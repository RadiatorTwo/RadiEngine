#include "radi/rd.h"
#include "IndexBuffer.h"

#include "radi/platform/opengl/GLIndexBuffer.h"
#include "radi/platform/directx/DXIndexBuffer.h"

#include "radi/graphics/API/Context.h"

namespace radi {
	namespace graphics {
		namespace API {

			IndexBuffer* IndexBuffer::Create(uint16* data, uint count)
			{
				switch (Context::GetRenderAPI())
				{
				case RenderAPI::OPENGL:		return rdnew GLIndexBuffer(data, count);
				case RenderAPI::DIRECT3D:	return rdnew D3DIndexBuffer(data, count);
				}
				return nullptr;
			}

			IndexBuffer* IndexBuffer::Create(uint* data, uint count)
			{
				switch (Context::GetRenderAPI())
				{
				case RenderAPI::OPENGL:		return rdnew GLIndexBuffer(data, count);
				case RenderAPI::DIRECT3D:	return rdnew D3DIndexBuffer(data, count);
				}
				return nullptr;
			}

		}
	}
}