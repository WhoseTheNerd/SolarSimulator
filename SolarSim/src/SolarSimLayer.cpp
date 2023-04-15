#include "SolarSimLayer.hpp"

#include <unordered_map>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <imgui.h>

#include <glm/gtc/matrix_transform.hpp>

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
        m_Entity = Pandora::CreateRef<Pandora::Entity>("SolarSim/assets/earth.obj");
        m_Entity->SetScale(0.25f);
        m_Entity->SetRotation({0.0f, 0.0f, 23.4f});
        m_Entity->SetPosition({0.0f, -0.5f, 0.0f});

        m_Texture = Pandora::Texture2D::Create("SolarSim/assets/earth.jpg");
        m_Texture->Bind();

        m_Shader = Pandora::Shader::Create("SolarSim/assets/basic.shader");
        m_Shader->Bind();  
        m_Shader->SetUniform("u_Texture", 0);
        m_Shader->SetUniform("u_UseTextures", 1);
        m_Shader->SetUniform("u_LightPos", glm::vec3{-2.0f, 12.0f, 12.0f});
        m_Shader->SetUniform("u_LightColor", Pandora::FromHex("#D3D3D3"));
        m_Shader->SetUniform("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());

        m_Shader->SetUniform("u_Model", m_Entity->GetModelMatrix());

        if (m_MouseCaptured) {
            glfwSetInputMode((GLFWwindow*)Pandora::Application::Get().GetWindow().GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }

    void SolarSimLayer::OnDetach()
    {

    }

    void SolarSimLayer::OnUpdate(Pandora::Timestep ts)
    {
        m_CameraController.OnUpdate(ts);
        m_Shader->SetUniform("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());

        glm::vec3 rotation = m_Entity->GetRotation();
        // 1 hour = 1 second
        rotation.y += (360.0f / (24.0f)) * ts;
        rotation.y = std::fmod(rotation.y, 360.0f);
        m_Entity->SetRotation(rotation);

        m_Shader->SetUniform("u_Model", m_Entity->GetModelMatrix());
    }

    void SolarSimLayer::OnRender()
    {
        Pandora::RenderCommand::SetClearColor({0.2f, 0.3f, 0.8f, 1.0f});
        Pandora::RenderCommand::Clear();
        
        Pandora::RenderCommand::DrawIndexed(m_Entity->GetMesh());
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
		        glfwSetInputMode((GLFWwindow*)Pandora::Application::Get().GetWindow().GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            } else {
		        glfwSetInputMode((GLFWwindow*)Pandora::Application::Get().GetWindow().GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
            }
            break;

        case Pandora::Key::G:
            wireframe_mode ^= true;
            if (wireframe_mode) {
                glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
            } else {
                glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
            }
            break;

        default: break;
        }

        return false;
    }

}