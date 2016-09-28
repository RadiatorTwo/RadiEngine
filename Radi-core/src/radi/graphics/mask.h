#pragma once

#include "radi/common.h"
#include "../maths/maths.h"
#include "texture.h"

namespace radi {
	namespace graphics {

		struct RD_API Mask
		{
			Texture* texture;
			maths::mat4 transform;

			Mask(Texture* texture, const maths::mat4& transform = maths::mat4::Identity())
				: texture(texture), transform(transform)
			{
				this->transform = maths::mat4::Scale(maths::vec3((float)texture->getWidth() / (float)texture->getHeight(), 1.0f, 1.0f));
			}

		};

	}
}