#pragma once

#include "Pandora/Graphics/Texture.hpp"

namespace Pandora {

    class OpenGLTexture3D : public Texture3D
    {
    public:
        OpenGLTexture3D(const std::array<std::string_view, 6>& files);
        virtual ~OpenGLTexture3D();

        virtual uint32_t GetWidth() const override { return m_Width; }
        virtual uint32_t GetHeight() const override { return m_Height; }

        virtual void Bind(uint32_t slot = 0) const override;
    private:
        uint32_t m_TextureHandle;
        uint32_t m_Width;
        uint32_t m_Height;
    };
}