#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/Entity.hpp"
#include "Pandora/Graphics/Texture.hpp"
#include "Pandora/Graphics/PerspectiveCamera.hpp"

namespace Pandora {

    class Renderer3D
    {
    public:
        static void Init();
		static void Shutdown();

        static void BeginScene(const PerspectiveCamera& camera);
        static void EndScene();

        static void DrawEntity(const Ref<Entity>& entity);
        static void DrawEntity(const Ref<Entity>& entity, Ref<Texture2D> texture);
    };
}