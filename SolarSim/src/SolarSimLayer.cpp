#include "SolarSimLayer.hpp"

#include <GL/glew.h>

namespace SolarSim {

    SolarSimLayer::SolarSimLayer()
        : m_Camera(-1.6f, 1.6f, -0.9f, 0.9f)
    {
    }

    SolarSimLayer::~SolarSimLayer()
    {
    }

    void SolarSimLayer::OnAttach()
    {
        m_VAO = Pandora::VertexArray::Create();

        float vertices[] = {
             0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
             0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
            -0.5f, -0.5f, 0.0f,  0.0f, 0.0f,
            -0.5f,  0.5f, 0.0f,  0.0f, 1.0f,
        };

        Pandora::Ref<Pandora::VertexBuffer> vbo = Pandora::VertexBuffer::Create(vertices, sizeof(vertices));
        Pandora::BufferLayout layout = {
            { Pandora::ShaderDataType::Float3, "a_Position" },
            { Pandora::ShaderDataType::Float2, "a_UV" }
        };
        vbo->SetLayout(layout);

        m_VAO->AddVertexBuffer(vbo);

        uint32_t indices[] = {
            0, 1, 3,
            1, 2, 3
        };

        Pandora::Ref<Pandora::IndexBuffer> ibo = Pandora::IndexBuffer::Create(indices, sizeof(indices) / sizeof(indices[0]));
        m_VAO->SetIndexBuffer(ibo);
        
        m_VAO->Bind();

        m_Texture = Pandora::Texture2D::Create("SolarSim/assets/wall.jpg");
        m_Texture->Bind();

        m_Shader = Pandora::Shader::Create("SolarSim/assets/basic.shader");
        m_Shader->Bind();  
        m_Shader->SetUniform("u_Texture", 0);
        m_Shader->SetUniform("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
    }

    void SolarSimLayer::OnDetach()
    {

    }

    void SolarSimLayer::OnUpdate(Pandora::Timestep ts)
    {
        const float SPEED = 2.5f * ts;
        if (Pandora::Input::IsKeyPressed(PD_KEY_W)) {
            glm::vec3 pos = m_Camera.GetPosition();
            pos.y -= SPEED;
            m_Camera.SetPosition(pos);
        }
        if (Pandora::Input::IsKeyPressed(PD_KEY_S)) {
            glm::vec3 pos = m_Camera.GetPosition();
            pos.y += SPEED;
            m_Camera.SetPosition(pos);
        }
        if (Pandora::Input::IsKeyPressed(PD_KEY_A)) {
            glm::vec3 pos = m_Camera.GetPosition();
            pos.x += SPEED;
            m_Camera.SetPosition(pos);
        }
        if (Pandora::Input::IsKeyPressed(PD_KEY_D)) {
            glm::vec3 pos = m_Camera.GetPosition();
            pos.x -= SPEED;
            m_Camera.SetPosition(pos);
        }
        m_Shader->SetUniform("u_ViewProjection", m_Camera.GetViewProjectionMatrix());
    }

    void SolarSimLayer::OnRender()
    {
        Pandora::RenderCommand::SetClearColor({0.2f, 0.3f, 0.8f, 1.0f});
        Pandora::RenderCommand::Clear();
        
        Pandora::RenderCommand::DrawIndexed(m_VAO);
    }

    void SolarSimLayer::OnEvent(Pandora::Event& event) 
    {
        Pandora::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Pandora::KeyPressedEvent>(PD_BIND_EVENT_FN(SolarSimLayer::OnKeyPressed));
    }

    bool SolarSimLayer::OnKeyPressed(Pandora::KeyPressedEvent& e)
    {
        constexpr float EQUAL_ANGLE_PARTS = 4.0f;

        switch (e.GetKeyCode())
        {
        case PD_KEY_Q:
            Pandora::Application::Get().SetRunning(false);
            break;

        case PD_KEY_KP_2:
        {
            float zoom = m_Camera.GetZoomLevel();
            zoom += 0.1f;
            if (zoom > 4.0f) {
                zoom = 4.0f;
            }
            m_Camera.SetZoomLevel(zoom);
            break;
        }

        case PD_KEY_KP_8:
        {
            float zoom = m_Camera.GetZoomLevel();
            zoom -= 0.1f;
            if (zoom < 0.05f) {
                zoom = 0.05f;
            }
            m_Camera.SetZoomLevel(zoom);
            break;
        }
        
        case PD_KEY_KP_4:
        {
            if (e.GetRepeatCount() == 1) break;

            float rot = m_Camera.GetRotation();
            rot -= 90.0f / EQUAL_ANGLE_PARTS;
            m_Camera.SetRotation(rot);

            break;
        }

        case PD_KEY_KP_6:
        {
            if (e.GetRepeatCount() == 1) break;

            float rot = m_Camera.GetRotation();
            rot += 90.0f / EQUAL_ANGLE_PARTS;
            m_Camera.SetRotation(rot);

            break;
        }

        default: break;
        }

        return false;
    }

}