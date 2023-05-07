#pragma once

#include "Pandora/Core/Base.hpp"

#include "Pandora/Graphics/Mesh.hpp"
#include "Pandora/Graphics/Shader.hpp"
#include "Pandora/Graphics/Texture.hpp"

namespace Pandora {

    class Skybox
    {
    public:
        Skybox(const char* shaderpath, const std::array<std::string, 6>& files);

        const Ref<Mesh>& GetMesh() const { return m_Mesh; }
        const Ref<Shader>& GetShader() const { return m_Shader; }
        const Ref<Texture3D>& GetCubeMap() const { return m_Cubemap; }
    private:
        Ref<Mesh> m_Mesh;
        Ref<Shader> m_Shader;
        Ref<Texture3D> m_Cubemap;
    };
}