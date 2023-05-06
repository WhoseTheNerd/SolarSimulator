#include "OpenGLTexture2D.hpp"

#include <GL/glew.h>
#include <stb_image.h>

namespace Pandora {

    Scope<Texture2D> Texture2D::Create(const char* filepath)
    {
        return CreateScope<OpenGLTexture2D>(filepath);
    }


    Scope<Texture2D> Texture2D::Create(const ImageData& imageData)
    {
        return CreateScope<OpenGLTexture2D>(imageData);
    }


    Texture2D::ImageData Texture2D::LoadImage(const char* filepath)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true); 
        uint8_t* data = stbi_load(filepath, &width, &height, &channels, 4);
        PD_CORE_ASSERT(data, "Failed to load texture!");

        return {data, width, height, channels};
    }

    OpenGLTexture2D::OpenGLTexture2D(const char* filepath)
    {
        int width, height, channels;
        stbi_set_flip_vertically_on_load(true); 
        uint8_t* data = stbi_load(filepath, &width, &height, &channels, 4);
        PD_CORE_ASSERT(data, "Failed to load texture!");

        m_Width = width;
        m_Height = height;

        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureHandle);
        glTextureStorage2D(m_TextureHandle, 1, GL_RGB8, m_Width, m_Height);

        glTextureParameteri(m_TextureHandle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureHandle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureHandle, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureHandle, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_TextureHandle, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, data);

        stbi_image_free(data);
    }

    OpenGLTexture2D::OpenGLTexture2D(const ImageData& imageData)
        : m_Width(imageData.width), m_Height(imageData.height)
    {
        glCreateTextures(GL_TEXTURE_2D, 1, &m_TextureHandle);
        glTextureStorage2D(m_TextureHandle, 1, GL_RGB8, m_Width, m_Height);

        glTextureParameteri(m_TextureHandle, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureHandle, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        glTextureParameteri(m_TextureHandle, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTextureParameteri(m_TextureHandle, GL_TEXTURE_WRAP_T, GL_REPEAT);

        glTextureSubImage2D(m_TextureHandle, 0, 0, 0, m_Width, m_Height, GL_RGBA, GL_UNSIGNED_BYTE, imageData.pixels);

        stbi_image_free(imageData.pixels);
    }

    OpenGLTexture2D::~OpenGLTexture2D()
    {
        glDeleteTextures(1, &m_TextureHandle);
    }

    void OpenGLTexture2D::Bind(uint32_t slot) const
    {
        glBindTextureUnit(slot, m_TextureHandle);
    }
}