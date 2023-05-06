#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/Entity.hpp"
#include "Pandora/Graphics/Texture.hpp"
#include "Pandora/Graphics/PerspectiveCamera.hpp"
#include "Pandora/Graphics/Skybox.hpp"

namespace Pandora {

    class Renderer3D
    {
    public:
        static void Init(const char* shaderpath);
		static void Shutdown();

        static void BeginScene(const PerspectiveCamera& camera);
        static void EndScene();

        static void DrawEntity(const Ref<Entity>& entity);

        static void SetSkybox(Scope<Skybox> skybox);
    };
}