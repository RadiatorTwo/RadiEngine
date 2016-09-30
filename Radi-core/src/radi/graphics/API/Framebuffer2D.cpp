#include "radi/rd.h"
#include "Framebuffer2D.h"

#include "context.h"

#include "radi/platform/opengl/GLFramebuffer2D.h"
#include "radi/platform/directx/DXFramebuffer2D.h"

#include "radi/system/Memory.h"

namespace radi { namespace graphics {

	Framebuffer2D* Framebuffer2D::Create(uint width, uint height)
	{
		switch (API::Context::GetRenderAPI())
		{
			case API::RenderAPI::OPENGL:	return rdnew GLFramebuffer2D(width, height);
			case API::RenderAPI::DIRECT3D:	return rdnew D3DFramebuffer2D(width, height);
		}
		return nullptr;
	}

} }