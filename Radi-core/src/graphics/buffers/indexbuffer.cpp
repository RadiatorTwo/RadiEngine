#include "indexbuffer.h"

namespace radi
{
	namespace graphics
	{
		IndexBuffer::IndexBuffer(short* data, uint count)
			:m_count(count)
		{
			GLCall(glGenBuffers(1, &m_bufferID));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(short), data, GL_STATIC_DRAW));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}

		IndexBuffer::IndexBuffer(uint* data, uint count)
			:m_count(count)
		{
			GLCall(glGenBuffers(1, &m_bufferID));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID));
			GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint), data, GL_STATIC_DRAW));
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}

		IndexBuffer::~IndexBuffer()
		{
			GLCall(glDeleteBuffers(1, &m_bufferID));
		}

		void IndexBuffer::bind() const
		{
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_bufferID));
		}

		void IndexBuffer::unbind() const
		{
			GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
		}
	}
}