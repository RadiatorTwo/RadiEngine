#include "vertexarray.h"

namespace radi
{
	namespace graphics
	{
		VertexArray::VertexArray()
		{
			GLCall(glGenVertexArrays(1, &m_arrayID));
		}

		VertexArray::~VertexArray()
		{
			for (uint i = 0; i < m_buffers.size(); i++)
				delete m_buffers[i];

			GLCall(glDeleteVertexArrays(1, &m_arrayID));
		}

		void VertexArray::addBuffer(Buffer* buffer, uint index)
		{
			bind();
			buffer->bind();

			GLCall(glEnableVertexAttribArray(index));
			GLCall(glVertexAttribPointer(index, buffer->getComponentCount(), GL_FLOAT, GL_FALSE, 0, 0));

			buffer->unbind();
			unbind();

			m_buffers.push_back(buffer);
		}

		void VertexArray::bind() const
		{
			GLCall(glBindVertexArray(m_arrayID));
		}

		void VertexArray::unbind() const
		{
			GLCall(glBindVertexArray(0));
		}
	}
}