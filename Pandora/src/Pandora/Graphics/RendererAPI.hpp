#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/VertexArray.hpp"

#include <glm/glm.hpp>

namespace Pandora {

    class RendererAPI
    {
    public:
        RendererAPI() = default;
        virtual ~RendererAPI() = default;

        virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        static Scope<RendererAPI> Create();
    };
}