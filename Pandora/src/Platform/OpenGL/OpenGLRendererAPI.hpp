#pragma once

#include "Pandora/Graphics/RendererAPI.hpp"

namespace Pandora {

    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        OpenGLRendererAPI();
        virtual ~OpenGLRendererAPI();

        virtual void SetClearColor(const glm::vec4& color) override;
		virtual void Clear() override;

		virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}