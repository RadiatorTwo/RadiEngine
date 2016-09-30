#pragma once

#include "radi/Common.h"
#include "radi/radi_types.h"

#include "radi/graphics/API/VertexBuffer.h"

namespace radi {
	namespace graphics {
		namespace API {

			class RD_API IndexBuffer
			{
			public:
				virtual void Bind() const = 0;
				virtual void Unbind() const = 0;

				virtual uint GetCount() const = 0;
			public:
				static IndexBuffer* Create(uint16* data, uint count);
				static IndexBuffer* Create(uint* data, uint count);
			};

		}
	}
}