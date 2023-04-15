#include "SolarSimLayer.hpp"

#include <unordered_map>

#include <GL/glew.h>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <tiny_obj_loader.h>

struct Vertex
{
    glm::vec3 Position;
    glm::vec2 TexCoords;

    bool operator==(const Vertex& other) const {
        return Position == other.Position && TexCoords == other.TexCoords;
    }
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.Position) ^
                   (hash<glm::vec2>()(vertex.TexCoords) << 1)));
        }
    };
}

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

        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        const std::string MODEL_PATH = "SolarSim/assets/viking_room.obj";

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, MODEL_PATH.c_str()))
        {
            throw std::runtime_error(warn + err);
        }

        std::vector<Vertex> vertices;
        std::vector<uint32_t> indices;

        std::unordered_map<Vertex, uint32_t> uniqueVertices{};

        for (const auto& shape : shapes) {
            for (const auto& index : shape.mesh.indices) {
                Vertex vertex{};

                vertex.Position = {
                    attrib.vertices[3 * index.vertex_index + 0],
                    attrib.vertices[3 * index.vertex_index + 1],
                    attrib.vertices[3 * index.vertex_index + 2],
                };

                vertex.TexCoords = {
                    attrib.texcoords[2 * index.texcoord_index + 0],
                    attrib.texcoords[2 * index.texcoord_index + 1],
                };

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }

                indices.push_back(uniqueVertices[vertex]);
            }
        }

        PD_INFO("Vertices: {}", vertices.size());

        Pandora::Ref<Pandora::VertexBuffer> vbo = Pandora::VertexBuffer::Create((const float*)vertices.data(), vertices.size() * sizeof(Vertex));
        Pandora::BufferLayout layout = {
            { Pandora::ShaderDataType::Float3, "a_Position" },
            { Pandora::ShaderDataType::Float2, "a_UV" }
        };
        vbo->SetLayout(layout);

        m_VAO->AddVertexBuffer(vbo);

        Pandora::Ref<Pandora::IndexBuffer> ibo = Pandora::IndexBuffer::Create(indices);
        m_VAO->SetIndexBuffer(ibo);
        
        m_VAO->Bind();

        m_Texture = Pandora::Texture2D::Create("SolarSim/assets/viking_room.png");
        m_Texture->Bind();

        m_Shader = Pandora::Shader::Create("SolarSim/assets/basic.shader");
        m_Shader->Bind();  
        m_Shader->SetUniform("u_Texture", 0);
        m_Shader->SetUniform("u_ViewProjection", m_CameraController.GetCamera().GetViewProjectionMatrix());

        glm::mat4 model = glm::rotate(glm::identity<glm::mat4>(), glm::radians(90.0f), glm::vec3{1, 0, 0});
        model = glm::rotate(model, glm::radians(180.0f), glm::vec3{0, 1, 0});
        model = glm::translate(model, glm::vec3{0.0f, 0.0f, -0.5f});
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