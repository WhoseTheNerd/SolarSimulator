#include "SolarSimLayer.hpp"

#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/string_cast.hpp>

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
        m_Entity = Pandora::CreateRef<Pandora::Entity>("SolarSim/assets/earth.obj", "SolarSim/assets/earth.jpg");
        m_Entity->SetScale(0.25f);
        m_Entity->SetRotation({0.0f, 0.0f, 23.4f});
        m_Entity->SetPosition({0.0f, -0.5f, 0.0f});

        if (m_MouseCaptured) {
            Pandora::Input::SetInputMode(Pandora::InputMode::Capture);
        }

        Pandora::RenderCommand::SetClearColor({0.2f, 0.3f, 0.8f, 1.0f});
        Pandora::Renderer3D::Init();

        m_CameraController.SetCameraPosition({-0.885036, 3.513909, 8.005553});
        m_CameraController.SetCameraPitch(-27.0f);
        m_CameraController.SetCameraYaw(-84.5047f);
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

        glm::vec3 rotation = m_Entity->GetRotation();
        // 1 hour = 1 second
        rotation.y += (360.0f / (24.0f)) * ts;
        rotation.y = std::fmod(rotation.y, 360.0f);
        m_Entity->SetRotation(rotation);
    }

    void SolarSimLayer::OnRender()
    {
        Pandora::Renderer3D::BeginScene(m_CameraController.GetCamera());
        Pandora::Renderer3D::DrawEntity(m_Entity);
        Pandora::Renderer3D::EndScene();
    }

    void SolarSimLayer::OnImGuiRender()
    {
        ImGui::Begin("Properties");
        ImGui::Text("Selected entity: %s", "Earth");
        
        glm::vec3 rotation = m_Entity->GetRotation();
        ImGui::SliderFloat3("Rotation", (float*)&rotation, -360.0f, 360.0f);
        m_Entity->SetRotation(rotation);

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