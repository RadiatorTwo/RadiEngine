#include "buffer.h"

namespace radi
{
	namespace graphics
	{
		Buffer::Buffer(GLfloat* data, GLsizei count, GLuint componentCount)
			:m_componentCount(componentCount)
		{
			GLCall(glGenBuffers(1, &m_bufferID));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferID));
			GLCall(glBufferData(GL_ARRAY_BUFFER, count * sizeof(GLfloat), data, GL_STATIC_DRAW));
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}

		Buffer::~Buffer()
		{
			GLCall(glDeleteBuffers(1, &m_bufferID));
		}

		void Buffer::bind() const
		{
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_bufferID));
		}

		void Buffer::unbind() const
		{
			GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
		}
	}
}