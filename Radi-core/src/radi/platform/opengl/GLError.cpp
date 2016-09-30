#include "radi/rd.h"

#include "radi/utils/Log.h"

#include "GLCommon.h"

namespace radi {

	GLenum GLCheckError()
	{
		return glGetError();
	}

	bool GLLogCall(const char* function, const char* file, int32 line)
	{
		GLenum error = GLCheckError();
		if (error != GL_NO_ERROR)
		{
			RADI_ERROR("[OpenGL Error] (", error, "): ", function, " ", file, ":", line);
			return false;
		}
		return true;
	}

}