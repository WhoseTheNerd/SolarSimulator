#pragma once

#include "Pandora/Graphics/Texture.hpp"

namespace Pandora {

    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const char* filepath);
        OpenGLTexture2D(const ImageData& imageData);
        virtual ~OpenGLTexture2D();

        virtual uint32_t GetWidth() const override { return m_Width; }
        virtual uint32_t GetHeight() const override { return m_Height; }

        virtual void Bind(uint32_t slot = 0) const override;
    private:
        uint32_t m_TextureHandle;
        uint32_t m_Width;
        uint32_t m_Height;
    };
}