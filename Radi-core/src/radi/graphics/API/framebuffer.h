#pragma once

#include "radi/Common.h"
#include "radi/radi_types.h"

#include "radi/maths/vec4.h"
#include "radi/maths/tvec2.h"

#include "Texture.h"

namespace radi {
	namespace graphics {

		class RD_API Framebuffer
		{
		public:
			virtual void Bind() const = 0;
			virtual void Unbind() const = 0;
			virtual void Clear() = 0;

			virtual uint GetWidth() const = 0;
			virtual uint GetHeight() const = 0;
			virtual API::Texture* GetTexture() const = 0;
		protected:
			virtual void Init() {};
		};

	}
}