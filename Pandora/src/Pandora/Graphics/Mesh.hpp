#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/VertexArray.hpp"

namespace Pandora {

    class Mesh
    {
    public:
        Mesh(const char* filepath);

        Ref<VertexArray> GetVAO() const { return m_VAO; }

    private:
        Ref<VertexArray> m_VAO;
    };
}