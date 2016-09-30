#include "radi/rd.h"
#include "TextureDepth.h"

#include "radi/platform/opengl/GLTextureDepth.h"
#include "radi/platform/directx/DXTextureDepth.h"

#include "radi/graphics/API/Context.h"

#include "radi/system/Memory.h"

namespace radi { namespace graphics { namespace API {

	TextureDepth* TextureDepth::Create(uint width, uint height)
	{
		switch (Context::GetRenderAPI())
		{
			case RenderAPI::OPENGL:		return rdnew GLTextureDepth(width, height);
			case RenderAPI::DIRECT3D:	return rdnew D3DTextureDepth(width, height);
		}
		return nullptr;
	}

} } }