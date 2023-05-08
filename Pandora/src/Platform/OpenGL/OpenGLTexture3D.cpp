#include "OpenGLTexture3D.hpp"

#include <vector>
#include <future>

#include <GL/glew.h>
#include <stb_image.h>

#define LOAD_MT 1

namespace Pandora {

    Scope<Texture3D> Texture3D::Create(const std::array<std::string, 6>& files)
    {
        return CreateScope<OpenGLTexture3D>(files);
    }

    OpenGLTexture3D::OpenGLTexture3D(const std::array<std::string, 6>& files)
    {
#if LOAD_MT
        glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &m_TextureHandle);

        struct RawImageData
        {
            uint8_t* pixels;
            int width;
            int height;
            int channels;
        };

        std::vector<std::future<RawImageData>> dataFutures;
        dataFutures.reserve(6);

        stbi_set_flip_vertically_on_load(false); 
        for (const auto& file : files) {
            dataFutures.push_back(std::async(std::launch::async, [](const std::string& file) {
                int width, height, channels;
                uint8_t* data = stbi_load(file.c_str(), &width, &height, &channels, 4);
                return RawImageData{data, width, height, channels};
            }, file));
        }

        for (const auto& future : dataFutures) {
            future.wait();
        }

        for (size_t i = 0; i < files.size(); ++i) {
            RawImageData rawImageData = dataFutures[i].get();

            if (rawImageData.pixels)
            {
                if (i == 0) {
                    m_Width = rawImageData.width;
                    m_Height = rawImageData.height;
                    glTextureStorage2D(m_TextureHandle, 1, GL_RGB8, m_Width, m_Height);
                }
                glTextureSubImage3D(m_TextureHandle, 0, 0, 0, i, rawImageData.width, rawImageData.height, 1, GL_RGBA, GL_UNSIGNED_BYTE, rawImageData.pixels);
                stbi_image_free(rawImageData.pixels);
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
    #else
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
        #endif
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