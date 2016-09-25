#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <utils/Log.h>

static void log_gl_call(const char* function, const char* file, int line)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		RADI_ERROR("[OpenGL Error] (", error, "): ", function, " ", file, ":", line);
	}
}

#ifdef RADI_DEBUG
#define GLCall(x) glGetError(); \
 		x; \
 		log_gl_call(#x, __FILE__, __LINE__);
#else
#define GLCall(x) x
#endif