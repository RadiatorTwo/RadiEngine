#pragma once

#include <radi/radi_types.h>
#include <radi/graphics/buffers/buffer_layout.h>

namespace radi {
	namespace graphics {
		namespace API {

			struct Buffer
			{
				uint id;
				uint target, usage;
				uint size;
				BufferLayout layout;

				Buffer(uint target, uint usage);
				~Buffer();

				void Resize(uint size);
				void SetData(uint size, const void* data);

				template<typename T>
				T* GetPointer(uint flags = 0x88B9/*GL_WRITE_ONLY*/)
				{
					return (T*)API::GetBufferPointer(target, flags);
				}

				void ReleasePointer();

				void Bind();
				void Unbind();
			};

		}
	}
}