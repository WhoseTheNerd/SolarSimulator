#include "SolarSimLayer.hpp"

#include <GL/glew.h>

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
        m_VAO = Pandora::VertexArray::Create();

        struct Vertex
        {
            glm::vec3 Position;
            glm::vec2 TexCoords;
        };

        const std::vector<Vertex> vertices = {
            {{ 0.5f,  0.5f, 0.0f}, {1.0f, 1.0f}},
            {{ 0.5f, -0.5f, 0.0f}, {1.0f, 0.0f}},
            {{-0.5f, -0.5f, 0.0f}, {0.0f, 0.0f}},
            {{-0.5f,  0.5f, 0.0f}, {0.0f, 1.0f}},
        };

        Pandora::Ref<Pandora::VertexBuffer> vbo = Pandora::VertexBuffer::Create((const float*)vertices.data(), vertices.size() * sizeof(Vertex));
        Pandora::BufferLayout layout = {
            { Pandora::ShaderDataType::Float3, "a_Position" },
            { Pandora::ShaderDataType::Float2, "a_UV" }
        };
        vbo->SetLayout(layout);

        m_VAO->AddVertexBuffer(vbo);

        const std::vector<uint32_t> indices = {
            0, 1, 3,
            1, 2, 3
        };

        Pandora::Ref<Pandora::IndexBuffer> ibo = Pandora::IndexBuffer::Create(indices);
        m_VAO->SetIndexBuffer(ibo);
        
        m_VAO->Bind();

        m_Texture = Pandora::Texture2D::Create("SolarSim/assets/wall.jpg");
        m_Texture->Bind();

        m_Shader = Pandora::Shader::Create("SolarSim/assets/basic.shader");
        m_Shader->Bind();  
        m_Shader->SetUniform("u_Texture", 0);
        m_Shader->SetUniform("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());
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
        
        Pandora::RenderCommand::DrawIndexed(m_VAO);
    }

    void SolarSimLayer::OnEvent(Pandora::Event& event) 
    {
        m_CameraController.OnEvent(event);

        Pandora::EventDispatcher dispatcher(event);
        dispatcher.Dispatch<Pandora::KeyPressedEvent>(PD_BIND_EVENT_FN(SolarSimLayer::OnKeyPressed));
    }

    bool SolarSimLayer::OnKeyPressed(Pandora::KeyPressedEvent& e)
    {
        switch (e.GetKeyCode())
        {
        case Pandora::Key::Escape:
            Pandora::Application::Get().SetRunning(false);
            break;

        default: break;
        }

        return false;
    }

}