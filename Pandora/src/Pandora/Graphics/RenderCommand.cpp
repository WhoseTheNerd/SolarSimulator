#include "RenderCommand.hpp"

namespace Pandora {

    Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();
}