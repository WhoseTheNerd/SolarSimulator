#pragma once

#include "Pandora/Graphics/Buffer.hpp"

namespace Pandora {

    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(const std::vector<float>& vertices);
        OpenGLVertexBuffer(const float* vertices, size_t size);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;

        virtual const BufferLayout& GetLayout() const override { return m_Layout; }
        virtual void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }

        friend class OpenGLVertexArray;
    private:
        uint32_t m_BufferHandle;
        BufferLayout m_Layout;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(const std::vector<uint32_t>& indices);
        OpenGLIndexBuffer(const uint32_t* indices, uint32_t count);
        virtual ~OpenGLIndexBuffer();

		virtual uint32_t GetCount() const override { return m_Count; }

        virtual void Bind() const override;

        friend class OpenGLVertexArray;
    private:
        uint32_t m_BufferHandle;
        uint32_t m_Count;
    };
}