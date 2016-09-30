#include "radi/rd.h"
#include "VertexArray.h"

#include "radi/platform/opengl/GLVertexArray.h"
#include "radi/platform/directx/DXVertexArray.h"

#include "radi/graphics/API/Context.h"
#include "radi/system/Memory.h"

namespace radi {
	namespace graphics {
		namespace API {

			VertexArray* VertexArray::Create()
			{
				switch (Context::GetRenderAPI())
				{
				case RenderAPI::OPENGL:		return rdnew GLVertexArray();
				case RenderAPI::DIRECT3D:	return rdnew D3DVertexArray();
				}
				return nullptr;
			}

		}
	}
}