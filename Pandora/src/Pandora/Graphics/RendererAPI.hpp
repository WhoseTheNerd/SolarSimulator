#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/VertexArray.hpp"
#include "Pandora/Graphics/Mesh.hpp"

#include <glm/glm.hpp>

namespace Pandora {

    enum class Face
    {
        Front, Back, FrontAndBack
    };

    enum class PolygonMode
    {
        Point, Line, Fill
    };

    enum class DepthFunctionMode
    {
        Never, Less, Equal, 
        LessEqual, Greater, 
        NotEqual, GreaterEqual, 
        Always
    };

    class RendererAPI
    {
    public:
        RendererAPI() = default;
        virtual ~RendererAPI() = default;

        virtual void SetClearColor(const glm::vec4& color) = 0;
		virtual void Clear() = 0;

		virtual void DrawIndexed(const Ref<Mesh>& mesh) = 0;

        virtual void SetPolygonMode(Face face, PolygonMode mode) = 0;

        virtual void SetDepthFunction(DepthFunctionMode mode) = 0;

        virtual void Viewport(int width, int height) = 0;

        static Scope<RendererAPI> Create();
    };
}