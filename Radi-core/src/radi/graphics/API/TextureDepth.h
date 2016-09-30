#pragma once

#include "Texture.h"

namespace radi { namespace graphics { namespace API {

	class RD_API TextureDepth : public Texture
	{
	public:
		static TextureDepth* Create(uint width, uint height);
	};

} } }