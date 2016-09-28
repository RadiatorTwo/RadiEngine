#pragma once

#include "radi/common.h"
#include "radi/radi_types.h"

#include "platform/opengl/radi_opengl_buffer.h"

namespace radi {
	namespace graphics {

		class RD_API IndexBuffer
		{
		private:
			uint m_Count;
			API::Buffer* m_Buffer;
		public:
			IndexBuffer(short* data, uint count);
			IndexBuffer(uint* data, uint count);
			~IndexBuffer();
			void Bind() const;
			void Unbind() const;

			inline uint GetCount() const { return m_Count; }
		};

	}
}