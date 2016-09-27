#include "vertexarray.h"

namespace radi
{
	namespace graphics
	{
		uint VertexArray::s_currentBinding = 0;

		VertexArray::VertexArray()
		{
			m_id = API::CreateVertexArray();
		}

		VertexArray::~VertexArray()
		{
			for (uint i = 0; i < m_buffers.size(); i++)
				delete m_buffers[i];

			API::FreeVertexArray(m_id);
		}

		API::Buffer* VertexArray::GetBuffer(uint index)
		{
			return m_buffers[index];
		}

		void VertexArray::PushBuffer(API::Buffer* buffer)
		{
			RADI_ASSERT(s_currentBinding == m_id);

			m_buffers.push_back(buffer);

			const std::vector<BufferLayoutType>& layout = buffer->layout.GetLayout();
			for (uint i = 0; i < layout.size(); i++)
			{
				API::EnableVertexAttribute(i);
				API::SetVertexAttributePointer(i, layout[i].count, layout[i].type, layout[i].normalized, buffer->layout.GetStride(), layout[i].offset);
			}
		}

		void VertexArray::bind() const
		{
#ifdef RADI_DEBUG
			s_currentBinding = m_id;
#endif
			API::BindVertexArray(m_id);
		}

		void VertexArray::unbind() const
		{
#ifdef RADI_DEBUG
			s_currentBinding = 0;
#endif
			API::UnbindVertexArrays();
		}

		void VertexArray::Draw(uint count) const
		{
			API::DrawElements(GL_TRIANGLES, count, GL_UNSIGNED_INT, NULL);
		}
	}
}