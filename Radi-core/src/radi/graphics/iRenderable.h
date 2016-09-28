#pragma once

#include "radi/common.h"

namespace radi {
	namespace graphics {

		class Renderer3D;

		class RD_API IRenderable
		{
		public:
			virtual void Render(Renderer3D& renderer) = 0;
		};

	}
}