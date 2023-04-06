#include "OpenGLVertexArray.hpp"

#include "OpenGLBuffer.hpp"

#include <GL/glew.h>

namespace Pandora {

    Scope<VertexArray> VertexArray::Create()
    {
        return CreateScope<OpenGLVertexArray>();
    }

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
	{
		switch (type)
		{
			case Pandora::ShaderDataType::Float:    return GL_FLOAT;
			case Pandora::ShaderDataType::Float2:   return GL_FLOAT;
			case Pandora::ShaderDataType::Float3:   return GL_FLOAT;
			case Pandora::ShaderDataType::Float4:   return GL_FLOAT;
			case Pandora::ShaderDataType::Mat3:     return GL_FLOAT;
			case Pandora::ShaderDataType::Mat4:     return GL_FLOAT;
			case Pandora::ShaderDataType::Int:      return GL_INT;
			case Pandora::ShaderDataType::Int2:     return GL_INT;
			case Pandora::ShaderDataType::Int3:     return GL_INT;
			case Pandora::ShaderDataType::Int4:     return GL_INT;
			case Pandora::ShaderDataType::Bool:     return GL_BOOL;
		}

		PD_CORE_ASSERT(false, "Unknown ShaderDataType!");
		return 0;
	}

    OpenGLVertexArray::OpenGLVertexArray()
    {
        glCreateVertexArrays(1, &m_VertexArrayHandle);
    }

    OpenGLVertexArray::~OpenGLVertexArray()
    {
        glDeleteVertexArrays(1, &m_VertexArrayHandle);
    }

    void OpenGLVertexArray::Bind() const
    {
        glBindVertexArray(m_VertexArrayHandle);
    }

    void OpenGLVertexArray::AddVertexBuffer(const Ref<VertexBuffer>& vertexBuffer)
    {
        PD_CORE_ASSERT(vertexBuffer->GetLayout().GetElements().size(), "Vertex Buffer has no layout!");

		const auto& layout = vertexBuffer->GetLayout();
		for (const auto& element : layout)
		{
			glEnableVertexArrayAttrib(m_VertexArrayHandle, m_VertexBufferIndex);
			glVertexArrayVertexBuffer(m_VertexArrayHandle, m_VertexBufferIndex,
				std::static_pointer_cast<OpenGLVertexBuffer>(vertexBuffer)->m_BufferHandle,
				element.Offset, layout.GetStride());
			glVertexArrayAttribFormat(m_VertexArrayHandle, m_VertexBufferIndex,
				element.GetComponentCount(),
				ShaderDataTypeToOpenGLBaseType(element.Type),
				element.Normalized ? GL_TRUE : GL_FALSE,
				0);

			glVertexArrayAttribBinding(m_VertexArrayHandle, m_VertexBufferIndex, m_VertexBufferIndex);
			m_VertexBufferIndex++;
		}

		m_VertexBuffers.push_back(vertexBuffer);
    }   

    void OpenGLVertexArray::SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer)
    {
        glVertexArrayElementBuffer(m_VertexArrayHandle, std::static_pointer_cast<OpenGLIndexBuffer>(indexBuffer)->m_BufferHandle);
        m_IndexBuffer = indexBuffer;
    }
}