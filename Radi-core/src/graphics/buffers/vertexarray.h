#pragma once

#include <vector>
#include <radigl.h>
#include <radi_types.h>
#include "buffer.h"

namespace radi
{
	namespace graphics
	{
		class VertexArray
		{
		private:
			GLuint m_arrayID;
			std::vector<Buffer*> m_buffers;
		public: 
			VertexArray();
			~VertexArray();
			void addBuffer(Buffer* buffer,GLuint index);
			void bind() const;
			void unbind() const;
		};
	}
}
