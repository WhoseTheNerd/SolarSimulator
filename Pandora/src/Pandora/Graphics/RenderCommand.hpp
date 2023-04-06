#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/VertexArray.hpp"
#include "Pandora/Graphics/RendererAPI.hpp"

#include <glm/glm.hpp>

namespace Pandora {

    class RenderCommand
    {
    public:
        inline static void SetClearColor(const glm::vec4& color)
		{
			s_RendererAPI->SetClearColor(color);
		}

		inline static void Clear()
		{
			s_RendererAPI->Clear();
		}

		inline static void DrawIndexed(const std::shared_ptr<VertexArray>& vertexArray)
		{
			s_RendererAPI->DrawIndexed(vertexArray);
		}
	private:
		static Scope<RendererAPI> s_RendererAPI;
    };
}