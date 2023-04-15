#include "SolarSimLayer.hpp"

#include <unordered_map>

#include <GL/glew.h>

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
        m_Mesh = Pandora::CreateRef<Pandora::Mesh>("SolarSim/assets/viking_room.obj");

        m_Texture = Pandora::Texture2D::Create("SolarSim/assets/viking_room.png");
        m_Texture->Bind();

        m_Shader = Pandora::Shader::Create("SolarSim/assets/basic.shader");
        m_Shader->Bind();  
        m_Shader->SetUniform("u_Texture", 0);
        m_Shader->SetUniform("u_UseTextures", 1);
        m_Shader->SetUniform("u_LightPos", glm::vec3{-2.0f, 12.0f, 12.0f});
        m_Shader->SetUniform("u_LightColor", Pandora::FromHex("#D3D3D3"));
        m_Shader->SetUniform("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());

        glm::mat4 model = glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3{1, 0, 0});
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3{0, 1, 0});
        model = glm::translate(model, glm::vec3{0.0f, 0.0f, -0.5f});
        model = glm::scale(model, glm::vec3{2.0f});
        m_Shader->SetUniform("u_Model", model);
    }

    void SolarSimLayer::OnDetach()
    {

    }

    void SolarSimLayer::OnUpdate(Pandora::Timestep ts)
    {
        m_CameraController.OnUpdate(ts);
        m_Shader->SetUniform("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());
    }

    void SolarSimLayer::OnRender()
    {
        Pandora::RenderCommand::SetClearColor({0.2f, 0.3f, 0.8f, 1.0f});
        Pandora::RenderCommand::Clear();
        
        Pandora::RenderCommand::DrawIndexed(m_Mesh);
    }

    void SolarSimLayer::OnEvent(Pandora::Event& event) 
    {
        m_CameraController.OnEvent(event);

        Pandora::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Pandora::KeyPressedEvent>(PD_BIND_EVENT_FN(SolarSimLayer::OnKeyPressed));
    }

    bool SolarSimLayer::OnKeyPressed(Pandora::KeyPressedEvent& e)
    {
        static bool wireframe_mode = false;

        switch (e.GetKeyCode())
        {
        case Pandora::Key::Escape:
            Pandora::Application::Get().SetRunning(false);
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