#pragma once

#include <string>

#include <radi/radi_types.h>
#include <radi/utils/log.h>

namespace radi {

	RD_API byte* load_image(const char* filename, uint* width, uint* height, uint* bits);

}