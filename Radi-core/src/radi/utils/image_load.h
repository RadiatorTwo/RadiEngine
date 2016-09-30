#pragma once

#include <string>

#include <radi/radi_types.h>
#include <radi/utils/Log.h>

#ifdef LoadImage
#undef LoadImage
#endif

namespace radi {

	RD_API byte* LoadImage(const char* filename, uint* width = nullptr, uint* height = nullptr, uint* bits = nullptr, bool flipY = false);
	RD_API byte* LoadImage(const String& filename, uint* width = nullptr, uint* height = nullptr, uint* bits = nullptr, bool flipY = false);

}