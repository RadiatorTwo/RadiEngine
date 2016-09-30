#include "radi/rd.h"
#include "GLContext.h"

#undef NOGDI
#include <Windows.h>
#define NOGDI
#include "radi/utils/Log.h"

#include <GL/glew.h>

namespace radi { namespace graphics { namespace API {

	static HDC hDc;

	GLContext::GLContext(WindowProperties, void* deviceContext)
	{
		hDc = GetDC((HWND)deviceContext);
		HGLRC hrc = wglCreateContext(hDc);
		if (hrc)
		{
			if (!wglMakeCurrent(hDc, hrc))
			{
				RADI_ERROR("Failed setting OpenGL context!");
				RADI_ASSERT(false);
			}
		}
		else
		{
			RADI_ERROR("Failed creating OpenGL context!");
			RADI_ASSERT(false);
		}

		if (glewInit() != GLEW_OK)
		{
			RADI_FATAL("Could not initialize GLEW!");
			RADI_ASSERT(false);
		}
	}

	void GLContext::Present()
	{
		SwapBuffers(hDc);
	}

} } }