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

		inline static void DrawIndexed(const Ref<Mesh>& mesh)
		{
			mesh->Bind();
			s_RendererAPI->DrawIndexed(mesh);
		}

		inline static void SetPolygonMode(Face face, PolygonMode mode)
		{
			s_RendererAPI->SetPolygonMode(face, mode);
		}

		inline static void SetDepthFunction(DepthFunctionMode mode)
		{
			s_RendererAPI->SetDepthFunction(mode);
		}

		inline static void Viewport(int width, int height)
		{
			s_RendererAPI->Viewport(width, height);
		}
	private:
		static inline Scope<RendererAPI> s_RendererAPI = RendererAPI::Create();
    };
}