#include "radi/rd.h"
#include "context.h"

#include "radi/platform/opengl/GLContext.h"
#include "radi/platform/directx/DXContext.h"

#include "radi/system/memory.h"

namespace radi { namespace graphics { namespace API {

	Context* Context::s_Context = nullptr;
	RenderAPI Context::s_RenderAPI = RenderAPI::NONE;

	void Context::Create(WindowProperties properties, void* deviceContext)
	{
		switch (GetRenderAPI())
		{
			case RenderAPI::OPENGL:		s_Context = rdnew GLContext(properties, deviceContext); break;
			case RenderAPI::DIRECT3D:	s_Context = rdnew D3DContext(properties, deviceContext); break;
		}
	}

} } }