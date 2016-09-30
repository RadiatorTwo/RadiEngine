#include "radi/rd.h"
#include "FramebufferDepth.h"

#include "Context.h"

#include "radi/platform/opengl/GLFramebufferDepth.h"
#include "radi/platform/directx/DXFramebufferDepth.h"

#include "radi/system/Memory.h"

namespace radi { namespace graphics {

	FramebufferDepth* FramebufferDepth::Create(uint width, uint height)
	{
		switch (API::Context::GetRenderAPI())
		{
			case API::RenderAPI::OPENGL:	return spnew GLFramebufferDepth(width, height);
			case API::RenderAPI::DIRECT3D:	return spnew D3DFramebufferDepth(width, height);
		}
		return nullptr;
	}

	
} }