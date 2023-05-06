#include "SolarSimLayer.hpp"

#include <unordered_map>
#include <iostream>
#include <future>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

#include <toml.hpp>

namespace SolarSim {

    SolarSimLayer::SolarSimLayer()
        : m_CameraController(1280.0f / 720.0f)
    {
    }

    SolarSimLayer::~SolarSimLayer()
    {
    }

    void SolarSimLayer::OnAttach()
    {
        Pandora::Timer timer("SolarSimLayer::OnAttach()");

        toml::table planets_file = toml::parse_file("SolarSim/assets/planets.toml");
        auto planets_list = planets_file["planets"]["names"].as_array();

        const float positional_constant = planets_file["planets"]["positional_constant"].value_or(5.0f);

        const float camera_speed = planets_file["camera"]["speed"].value_or(5.0f);

        const float camera_pitch = planets_file["camera"]["pitch"].value_or(-90.0f);
        const float camera_yaw = planets_file["camera"]["yaw"].value_or(0.0f);
        const float camera_pos_x = planets_file["camera"]["position"].as_array()->at(0).value_or(0.0f);
        const float camera_pos_y = planets_file["camera"]["position"].as_array()->at(1).value_or(0.0f);
        const float camera_pos_z = planets_file["camera"]["position"].as_array()->at(2).value_or(0.0f);

        m_CameraController.SetTranslationSpeed(camera_speed);
        m_CameraController.SetCameraPitch(camera_pitch);
        m_CameraController.SetCameraYaw(camera_yaw);
        m_CameraController.SetCameraPosition(glm::vec3{camera_pos_x, camera_pos_y, camera_pos_z});

        struct PlanetData
        {
            std::string modelPath;
            std::string texturePath;
            float mass;
            float radius;
            float distance;

            PlanetData(const std::string& modelPath, const std::string& texturePath, float mass, float radius, float distance)
                : modelPath(modelPath), texturePath(texturePath), mass(mass), radius(radius), distance(distance)
            {}
        };

        std::vector<PlanetData> planetsData;
        planetsData.reserve(planets_list->size());

        planets_list->for_each([&](auto&& el) {
            const std::string name = el.value_or("");
            const std::string modelpath = std::string("SolarSim/assets/models/") + planets_file[name]["model"].value_or("");
            const std::string texturepath = std::string("SolarSim/assets/textures/") + planets_file[name]["texture"].value_or("");
            const float mass = planets_file[name]["mass"].value_or(-1.0f);
            const float radius = planets_file[name]["radius"].value_or(-1.0f);
            const float distance = planets_file[name]["distance"].value_or(-1.0f);
            planetsData.emplace_back(modelpath, texturepath, mass, radius, distance);
        });

        struct PureMesh
        {
            std::vector<Pandora::Vertex> vertices;
            std::vector<uint32_t> indices;
        };                    

        std::vector<std::future<PureMesh>> pureMeshesFuture;

        for (const auto& planetData : planetsData) {
            pureMeshesFuture.push_back(std::async(std::launch::async, [](const std::string& modelpath){
                auto [vertices, indices] = Pandora::Mesh::LoadMesh(modelpath.c_str());
                return PureMesh{vertices, indices};
            }, planetData.modelPath));
        }

        for (const auto& future : pureMeshesFuture) {
            future.wait();
        }

        PD_ASSERT(pureMeshesFuture.size() == planetsData.size(), "Something wrong going around here.");

        for (size_t i = 0; i < planetsData.size(); ++i) {
            PlanetData planetData = planetsData[i];
            PureMesh pureMesh = pureMeshesFuture[i].get();

            const Pandora::Ref<Pandora::Mesh> mesh = Pandora::CreateRef<Pandora::Mesh>(pureMesh.vertices, pureMesh.indices);

            const float scale = planetData.radius / planets_file["Earth"]["radius"].value_or(1.0f);

            auto planet = Pandora::CreateRef<Pandora::Entity>(mesh, planetData.texturePath.c_str());
            planet->SetPosition({positional_constant * i, -0.5f, 0.0f});
            planet->SetScale({scale});
            m_Planets.push_back(planet);
        }

        if (m_MouseCaptured) {
            Pandora::Input::SetInputMode(Pandora::InputMode::Capture);
        }

        Pandora::RenderCommand::SetClearColor({0.2f, 0.3f, 0.8f, 1.0f});
        Pandora::Renderer3D::Init("SolarSim/assets/shaders/basic.shader");

        const std::array<std::string_view, 6> files = {
            "SolarSim/assets/textures/skybox/right.jpg",
            "SolarSim/assets/textures/skybox/left.jpg",
            "SolarSim/assets/textures/skybox/top.jpg",
            "SolarSim/assets/textures/skybox/bottom.jpg",
            "SolarSim/assets/textures/skybox/front.jpg",
            "SolarSim/assets/textures/skybox/back.jpg",
        };

        Pandora::Scope<Pandora::Skybox> skybox = Pandora::CreateScope<Pandora::Skybox>("SolarSim/assets/shaders/skybox.shader", files);
        Pandora::Renderer3D::SetSkybox(std::move(skybox));
    }

    void SolarSimLayer::OnDetach()
    { 
        Pandora::Renderer3D::Shutdown();
    }

    void SolarSimLayer::OnUpdate(Pandora::Timestep ts)
    {
        static float startTime = 0.0f;
        static double sum = 0.0;
        static uint64_t count = 0;

        const float fps = 1.0f / ts;
        sum += fps;
        count++;

        const float endTime = Pandora::Platform::GetTime();
        const float duration = endTime - startTime;
        if (duration >= 1.0f) {
            char buf[80];
            int written = snprintf(buf, sizeof(buf), "Solar system simulator - %d fps", static_cast<uint32_t>(std::round(sum / static_cast<double>(count))));
            if (written >= sizeof(buf)) {
                PD_WARN("Output truncated!");
            }
            Pandora::Application::Get().GetWindow().SetWindowTitle(buf);
            sum = 0.0;
            count = 0;

            startTime = endTime;
        }

        m_CameraController.OnUpdate(ts);

        /*for (auto planet : m_Planets) {
            glm::vec3 rotation = planet->GetRotation();
            // 1 hour = 1 second
            rotation.y += (360.0f / (24.0f)) * ts;
            rotation.y = std::fmod(rotation.y, 360.0f);
            planet->SetRotation(rotation);
        }*/
    }

    void SolarSimLayer::OnRender()
    {
        Pandora::Renderer3D::BeginScene(m_CameraController.GetCamera());
        for (auto planet : m_Planets) {
            Pandora::Renderer3D::DrawEntity(planet);
        }
        Pandora::Renderer3D::EndScene();
    }

    void SolarSimLayer::OnImGuiRender()
    {
        ImGui::Begin("Properties");
        ImGui::Text("Selected entity: %s", "Earth");

        ImGui::Text("Camera Position: %.2f %.2f %.2f", m_CameraController.GetCamera().GetPosition().x, m_CameraController.GetCamera().GetPosition().y, m_CameraController.GetCamera().GetPosition().z);
        ImGui::Text("Camera Yaw & Pitch: %.2f & %.2f", m_CameraController.GetCamera().GetYaw(), m_CameraController.GetCamera().GetPitch());

        float camera_speed = m_CameraController.GetTranslationSpeed();
        ImGui::SliderFloat("Camera speed", &camera_speed, 80.0f, 500.0f);
        m_CameraController.SetTranslationSpeed(camera_speed);

        ImGui::End();
    }

    void SolarSimLayer::OnEvent(Pandora::Event& event) 
    {
        if (m_MouseCaptured) {
            m_CameraController.OnEvent(event);
        }

        Pandora::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Pandora::KeyPressedEvent>(PD_BIND_EVENT_FN(SolarSimLayer::OnKeyPressed));
    }

    bool SolarSimLayer::OnKeyPressed(Pandora::KeyPressedEvent& e)
    {
        static bool wireframe_mode = false;

        switch (e.GetKeyCode())
        {
        case Pandora::Key::Escape:
            m_MouseCaptured ^= true;
            if (m_MouseCaptured) {
                m_CameraController.SetFirstMouseEvent(true);
                Pandora::Input::SetInputMode(Pandora::InputMode::Capture);
            } else {
                Pandora::Input::SetInputMode(Pandora::InputMode::Normal);
            }
            break;

        case Pandora::Key::G:
            wireframe_mode ^= true;
            if (wireframe_mode) {
                Pandora::RenderCommand::SetPolygonMode(Pandora::Face::FrontAndBack, Pandora::PolygonMode::Line);
            } else {
                Pandora::RenderCommand::SetPolygonMode(Pandora::Face::FrontAndBack, Pandora::PolygonMode::Fill);
            }
            break;

        default: break;
        }

        return false;
    }

}