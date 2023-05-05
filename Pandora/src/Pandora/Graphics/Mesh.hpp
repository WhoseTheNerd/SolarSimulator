#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/VertexArray.hpp"

namespace Pandora {

    class Mesh
    {
    public:
        Mesh(const char* filepath);

        Ref<VertexArray> GetVAO() const { return m_VAO; }

        void Bind() const;

    private:
        Ref<VertexArray> m_VAO;
    };
}