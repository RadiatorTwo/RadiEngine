#pragma once

#include "radi/radi_types.h"
#include "radi/maths/maths.h"

namespace radi {
	namespace graphics {

		struct RD_API Light
		{
			maths::vec3 position;
			float attenuation;
			maths::vec4 color;
		};

	}
}