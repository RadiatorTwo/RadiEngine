#include "indexbuffer.h"

namespace radi
{
	namespace graphics
	{
		IndexBuffer::IndexBuffer(short* data, uint count)
			:m_count(count)
		{
			m_buffer = new API::Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			m_buffer->Bind();
			m_buffer->SetData(count * sizeof(short), data);
			m_buffer->Unbind();
		}

		IndexBuffer::IndexBuffer(uint* data, uint count)
			:m_count(count)
		{
			m_buffer = new API::Buffer(GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
			m_buffer->Bind();
			m_buffer->SetData(count * sizeof(uint), data);
			m_buffer->Unbind();
		}

		IndexBuffer::~IndexBuffer()
		{
			delete m_buffer;
		}

		void IndexBuffer::bind() const
		{
			m_buffer->Bind();
		}

		void IndexBuffer::unbind() const
		{
			m_buffer->Unbind();
		}
	}
}