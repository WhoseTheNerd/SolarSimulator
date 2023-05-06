#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/Vertex.hpp"
#include "Pandora/Graphics/VertexArray.hpp"

namespace Pandora {

    class Mesh
    {
    public:
        Mesh(const char* filepath);
        Mesh(const std::vector<Vertex>& vertices, const std::vector<uint32_t>& indices);

        template<size_t N1, size_t N2>
        Mesh(const std::array<float, N1>& vertices, const std::array<uint32_t, N2>& indices, const BufferLayout& layout)
        {
            InitMesh(vertices.size(), vertices.data(), indices.size(), indices.data(), layout);
        }

        void InitMesh(size_t vertices_len, const float* vertices, size_t indices_len, const uint32_t* indices, const BufferLayout& layout);

        Ref<VertexArray> GetVAO() const { return m_VAO; }

        void Bind() const;

        static std::pair<std::vector<Vertex>, std::vector<uint32_t>> LoadMesh(const char* filepath);

    private:
        Ref<VertexArray> m_VAO;
    };
}