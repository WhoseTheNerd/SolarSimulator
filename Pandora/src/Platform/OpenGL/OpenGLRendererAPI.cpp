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
}