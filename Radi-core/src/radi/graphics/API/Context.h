#pragma once

#include "radi/Common.h"
#include "radi/app/Window.h"

namespace radi { namespace graphics { namespace API {

	enum class RD_API RenderAPI
	{
		NONE, OPENGL, DIRECT3D
	};

	class RD_API Context
	{
	protected:
		static Context* s_Context;
		static RenderAPI s_RenderAPI;
	public:
		static void Create(WindowProperties properties, void* deviceContext);

		static RenderAPI GetRenderAPI() { return s_RenderAPI; }
		static void SetRenderAPI(RenderAPI api) { s_RenderAPI = api; }
	};

} } }