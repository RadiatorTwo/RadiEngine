#include "radi/rd.h"
#include "renderer.h"

#include "radi/platform/opengl/GLRenderer.h"
#include "radi/platform/directx/DXRenderer.h"

#include "API/Context.h"
#include "radi/system/Memory.h"

namespace radi {
	namespace graphics {

		Renderer* Renderer::s_Instance = nullptr;

		void Renderer::Init()
		{
			switch (API::Context::GetRenderAPI())
			{
			case API::RenderAPI::OPENGL:	s_Instance = rdnew GLRenderer(); break;
			case API::RenderAPI::DIRECT3D:	s_Instance = rdnew D3DRenderer(); break;
			}
			s_Instance->InitInternal();
		}

	}
}