#include "OpenGLBuffer.hpp"

#include <GL/glew.h>

namespace Pandora {

    Scope<VertexBuffer> VertexBuffer::Create(const std::vector<float>& vertices)
    {
        return CreateScope<OpenGLVertexBuffer>(vertices);
    }

    Scope<VertexBuffer> VertexBuffer::Create(const float* vertices, size_t size)
    {
        return CreateScope<OpenGLVertexBuffer>(vertices, size);
    }

    Scope<IndexBuffer> IndexBuffer::Create(const std::vector<uint32_t>& indices)
    {
        return CreateScope<OpenGLIndexBuffer>(indices);
    }

    Scope<IndexBuffer> IndexBuffer::Create(const uint32_t* indices, uint32_t count)
    {
        return CreateScope<OpenGLIndexBuffer>(indices, count);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(const std::vector<float>& vertices)
    {
        glCreateBuffers(1, &m_BufferHandle);
        glNamedBufferData(m_BufferHandle, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::OpenGLVertexBuffer(const float* vertices, size_t size)
    {
        glCreateBuffers(1, &m_BufferHandle);
        glNamedBufferData(m_BufferHandle, size, vertices, GL_STATIC_DRAW);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_BufferHandle);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_BufferHandle);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(const std::vector<uint32_t>& indices)
        : m_Count(indices.size())
    {
        glCreateBuffers(1, &m_BufferHandle);
        glNamedBufferData(m_BufferHandle, indices.size() * sizeof(uint32_t), indices.data(), GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::OpenGLIndexBuffer(const uint32_t* indices, uint32_t count)
        : m_Count(count)
    {
        glCreateBuffers(1, &m_BufferHandle);
        glNamedBufferData(m_BufferHandle, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_BufferHandle);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_BufferHandle);
    }
}