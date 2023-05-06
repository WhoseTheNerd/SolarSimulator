#pragma once

#include "Pandora/Core/Base.hpp"

namespace Pandora {

    class Texture
    {
    public:
        Texture() = default;
        virtual ~Texture() = default;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual void Bind(uint32_t slot = 0) const = 0;
    };

    class Texture2D : public Texture
    {
    public:
        struct ImageData
        {
            uint8_t* pixels;
            int width;
            int height;
            int channels;
        };
    public:
        static ImageData LoadImage(const char* filepath);

        static Scope<Texture2D> Create(const char* filepath);
        static Scope<Texture2D> Create(const ImageData& imageData);
    };

    class Texture3D : public Texture
    {
    public:
        static Scope<Texture3D> Create(const std::array<std::string_view, 6>& files);
    };
}