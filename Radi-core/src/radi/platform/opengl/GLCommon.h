#pragma once

#include <GL/glew.h>

namespace radi {
	extern GLenum GLCheckError();
	extern bool GLLogCall(const char* function, const char* file, int32 line);
}

#ifdef RADI_DEBUG
	#define GLCall(x) radi::GLCheckError();\
		x; \
		if (!radi::GLLogCall(#x, __FILE__, __LINE__)) __debugbreak();
#else
	#define GLCall(x) x
#endif
