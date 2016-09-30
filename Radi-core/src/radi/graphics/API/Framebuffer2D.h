#pragma once

#include "Framebuffer.h"

namespace radi { namespace graphics {

	class RD_API Framebuffer2D : public Framebuffer
	{
	public:
		virtual void SetClearColor(const maths::vec4& color) = 0;
	public:
		static Framebuffer2D* Create(uint width, uint height);
	};

} }