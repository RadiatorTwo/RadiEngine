#include "radi/rd.h"
#include "VertexBuffer.h"

#include "radi/platform/opengl/GLVertexBuffer.h"
#include "radi/platform/directx/DXVertexBuffer.h"

#include "radi/graphics/API/Context.h"

namespace radi { namespace graphics { namespace API {

	VertexBuffer* VertexBuffer::Create(BufferUsage usage)
	{
		switch (Context::GetRenderAPI())
		{
			case RenderAPI::OPENGL:		return rdnew GLVertexBuffer(usage);
			case RenderAPI::DIRECT3D:	return rdnew D3DVertexBuffer(usage);
		}
		return nullptr;
	}

} } }