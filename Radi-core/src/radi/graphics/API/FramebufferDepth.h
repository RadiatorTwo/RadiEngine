#pragma once

#include "Framebuffer.h"

namespace radi { namespace graphics {

	class RD_API FramebufferDepth : public Framebuffer
	{
	public:
		static FramebufferDepth* Create(uint width, uint height);
	};

} }