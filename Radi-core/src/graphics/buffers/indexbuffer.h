#pragma once

#include <radi_types.h>
#include "../radi_render_api.h"

namespace radi
{
	namespace graphics
	{
		class IndexBuffer
		{
		private:
			uint m_count;
			API::Buffer* m_buffer;

		public:
			IndexBuffer(short* data, uint count);
			IndexBuffer(uint* data, uint count);
			~IndexBuffer();

			void bind() const;
			void unbind() const;

			inline uint GetCount() const { return m_count; }
		};

	}
}