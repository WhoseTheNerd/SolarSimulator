#include "OpenGLRendererAPI.hpp"

#include <GL/glew.h>

namespace Pandora {

    Scope<RendererAPI> RendererAPI::Create()
    {
        return CreateScope<OpenGLRendererAPI>();
    }

    OpenGLRendererAPI::OpenGLRendererAPI()
    {
    }

    OpenGLRendererAPI::~OpenGLRendererAPI()
    {
    }

    void OpenGLRendererAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }
    
    void OpenGLRendererAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRendererAPI::DrawIndexed(const Ref<Mesh>& mesh)
    {
        glDrawElements(GL_TRIANGLES, mesh->GetVAO()->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }

    void OpenGLRendererAPI::SetPolygonMode(Face face, PolygonMode mode)
    {
        GLenum glface;
        switch (face)
        {
        case Face::Front:
            glface = GL_FRONT;
            break;
        case Face::Back:
            glface = GL_BACK;
            break;
        case Face::FrontAndBack:
            glface = GL_FRONT_AND_BACK;
            break;
        default:
            PD_CORE_ASSERT(false, "End of unreachable switch statement!");
        }

        GLenum glmode;
        switch (mode)
        {
        case PolygonMode::Fill:
            glmode = GL_FILL;
            break;
        case PolygonMode::Line:
            glmode = GL_LINE;
            break;
        case PolygonMode::Point:
            glmode = GL_POINT;
            break;

        default: PD_CORE_ASSERT(false, "End of unreachable switch statement!");
        }

        glPolygonMode(glface, glmode);
    }


    void OpenGLRendererAPI::SetDepthFunction(DepthFunctionMode mode)
    {
        switch (mode)
        {
        case DepthFunctionMode::Never:
            glDepthFunc(GL_NEVER);
            break;
        case DepthFunctionMode::Less:
            glDepthFunc(GL_LESS);
            break;
        case DepthFunctionMode::Equal:
            glDepthFunc(GL_EQUAL);
            break;
        case DepthFunctionMode::LessEqual:
            glDepthFunc(GL_LEQUAL);
            break;
        case DepthFunctionMode::Greater:
            glDepthFunc(GL_GREATER);
            break;
        case DepthFunctionMode::NotEqual:
            glDepthFunc(GL_NOTEQUAL);
            break;
        case DepthFunctionMode::GreaterEqual:
            glDepthFunc(GL_GEQUAL);
            break;
        case DepthFunctionMode::Always:
            glDepthFunc(GL_ALWAYS);
            break;
        default:
            throw std::runtime_error("End of unreachable section reached!");
        }
    }

    void OpenGLRendererAPI::Viewport(int width, int height)
    {
        glViewport(0, 0, width, height);
    }
}