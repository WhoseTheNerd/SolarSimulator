#include "OpenGLTexture3D.hpp"

#include <GL/glew.h>
#include <stb_image.h>

namespace Pandora {

    Scope<Texture3D> Texture3D::Create(const std::array<std::string_view, 6>& files)
    {
        return CreateScope<OpenGLTexture3D>(files);
    }

    OpenGLTexture3D::OpenGLTexture3D(const std::array<std::string_view, 6>& files)
    {
        glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_TextureHandle);

        for (size_t i = 0; i < files.size(); ++i)
        {
            int width, height, channels;

            stbi_set_flip_vertically_on_load(false); 
            uint8_t* data = stbi_load(files[i].data(), &width, &height, &channels, 4);

            if (data)
            {
                if (i == 0) {
                    m_Width = width;
                    m_Height = height;
                    glTextureStorage2D(m_TextureHandle, 1, GL_RGB8, m_Width, m_Height);
                }

                glTextureSubImage3D(m_TextureHandle, 0, 0, 0, i, width, height, 1, GL_RGBA, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            else
            {
                throw std::runtime_error("Failed to load texture!");
            }
        }

        glTextureParameteri(m_TextureHandle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureHandle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTextureParameteri(m_TextureHandle, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_TextureHandle, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTextureParameteri(m_TextureHandle, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    }

    OpenGLTexture3D::~OpenGLTexture3D()
    {
        glDeleteTextures(1, &m_TextureHandle);
    }   

    void OpenGLTexture3D::Bind(uint32_t slot) const
    { 
        glBindTextureUnit(slot, m_TextureHandle);
    }
}