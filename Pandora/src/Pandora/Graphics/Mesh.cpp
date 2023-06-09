#include "Mesh.hpp"

#include "Pandora/Graphics/Buffer.hpp"
#include "Pandora/Graphics/Vertex.hpp"

#include <tiny_obj_loader.h>

namespace Pandora {

    Mesh::Mesh(const char* filepath)
    {
        const auto [vertices, indices] = LoadMesh(filepath);

        m_VAO = VertexArray::Create();

        Ref<VertexBuffer> vbo = VertexBuffer::Create((const float*)vertices.data(), vertices.size() * sizeof(Vertex));
        vbo->SetLayout(Vertex::GetBufferLayout());

        Ref<IndexBuffer> ibo = IndexBuffer::Create(indices);

        m_VAO->AddVertexBuffer(vbo);
        m_VAO->SetIndexBuffer(ibo);
    }


    Mesh::Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices)
    {
        m_VAO = VertexArray::Create();

        Ref<VertexBuffer> vbo = VertexBuffer::Create((const float*)vertices.data(), vertices.size() * sizeof(Vertex));
        vbo->SetLayout(Vertex::GetBufferLayout());

        Ref<IndexBuffer> ibo = IndexBuffer::Create(indices);

        m_VAO->AddVertexBuffer(vbo);
        m_VAO->SetIndexBuffer(ibo);
    }

    void Mesh::InitMesh(size_t vertices_len, const float* vertices, size_t indices_len, const uint32_t* indices, const BufferLayout& layout)
    {
        m_VAO = VertexArray::Create();

        Ref<VertexBuffer> vbo = VertexBuffer::Create(vertices, vertices_len * sizeof(float));
        vbo->SetLayout(layout);

        Ref<IndexBuffer> ibo = IndexBuffer::Create(indices, indices_len);

        m_VAO->AddVertexBuffer(vbo);
        m_VAO->SetIndexBuffer(ibo);
    }

    void Mesh::Bind() const
    {
        m_VAO->Bind();
    }

    std::pair<std::vector<Vertex>, std::vector<uint32_t>> Mesh::LoadMesh(const char* filepath)
    {
        tinyobj::attrib_t attrib;
        std::vector<tinyobj::shape_t> shapes;
        std::vector<tinyobj::material_t> materials;
        std::string warn, err;

        if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &warn, &err, filepath))
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
                
                vertex.Normal = {
                    attrib.normals[3 * index.normal_index + 0],
                    attrib.normals[3 * index.normal_index + 1],
                    attrib.normals[3 * index.normal_index + 2],
                };

                if (uniqueVertices.count(vertex) == 0) {
                    uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
                    vertices.push_back(vertex);
                }

                indices.push_back(uniqueVertices[vertex]);
            }
        }

        return std::make_pair(vertices, indices);
    }
}