#pragma once

#include <radi_types.h>
#include <radigl.h>

namespace radi
{
	namespace graphics
	{
		class IndexBuffer
		{
		private:
			GLuint m_bufferID;
			GLuint m_count;

		public:
			IndexBuffer(short* data, uint count);
			IndexBuffer(uint* data, uint count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline GLuint getCount() const { return m_count; }
		};

	}
}