#include "Skybox.hpp"

namespace Pandora {

    constexpr std::array<float, 24> SKYBOX_VERTICES = {
        //   Coordinates
        -1.0f, -1.0f,  1.0f,    //        7--------6
         1.0f, -1.0f,  1.0f,    //       /|       /|
         1.0f, -1.0f, -1.0f,    //      4--------5 |
        -1.0f, -1.0f, -1.0f,    //      | |      | |
        -1.0f,  1.0f,  1.0f,    //      | 3------|-2
         1.0f,  1.0f,  1.0f,    //      |/       |/
         1.0f,  1.0f, -1.0f,    //      0--------1
        -1.0f,  1.0f, -1.0f
    };

    constexpr std::array<uint32_t, 36> SKYBOX_INDICES = {
        // Right
        1, 2, 6,
        6, 5, 1,
        // Left
        0, 4, 7,
        7, 3, 0,
        // Top
        4, 5, 6,
        6, 7, 4,
        // Bottom
        0, 3, 2,
        2, 1, 0,
        // Back
        0, 1, 5,
        5, 4, 0,
        // Front
        3, 7, 6,
        6, 2, 3
    };

    const static BufferLayout SKYBOX_LAYOUT = {
        { Pandora::ShaderDataType::Float3, "aPos" },
    };

    Skybox::Skybox(const char* shaderpath, const std::array<std::string, 6>& files)
        : m_Mesh(CreateRef<Mesh>(SKYBOX_VERTICES, SKYBOX_INDICES, SKYBOX_LAYOUT)), 
          m_Shader(Shader::Create(shaderpath)), 
          m_Cubemap(Texture3D::Create(files))
    {
        m_Shader->SetUniform("skybox", 0);
    }
}