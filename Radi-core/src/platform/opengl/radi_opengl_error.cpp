#include "radi/rd.h"

#include "radi/utils/Log.h"

#include <GL/glew.h>

void check_error()
{
	glGetError();
}

bool log_gl_call(const char* function, const char* file, int line)
{
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		RADI_ERROR("[OpenGL Error] (", error, "): ", function, " ", file, ":", line);
		return false;
	}
	return true;
}