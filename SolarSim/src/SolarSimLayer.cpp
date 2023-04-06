#include "SolarSimLayer.hpp"

#include <GL/glew.h>

namespace SolarSim {

    SolarSimLayer::SolarSimLayer()
    {
    }

    SolarSimLayer::~SolarSimLayer()
    {
    }

    void SolarSimLayer::OnAttach()
    {
        m_VAO = Pandora::VertexArray::Create();

        float vertices[] = {
             0.5f,  0.5f, 0.0f,
             0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f,
            -0.5f,  0.5f, 0.0f
        };

        Pandora::Ref<Pandora::VertexBuffer> vbo = Pandora::VertexBuffer::Create(vertices, sizeof(vertices));
        Pandora::BufferLayout layout = {
            { Pandora::ShaderDataType::Float3, "a_Position" }
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

        m_Shader = Pandora::Shader::Create("SolarSim/assets/basic.shader");
        m_Shader->Bind();     
    }

    void SolarSimLayer::OnDetach()
    {

    }

    void SolarSimLayer::OnUpdate(Pandora::Timestep ts)
    {

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
        dispatcher.Dispatch<Pandora::MouseMovedEvent>(PD_BIND_EVENT_FN(SolarSimLayer::OnMouseMoveEvent));
    }

    bool SolarSimLayer::OnMouseMoveEvent(Pandora::MouseMovedEvent& e)
    {
        return false;
    }

}