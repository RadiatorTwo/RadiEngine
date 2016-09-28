#pragma once

#include "radi/common.h"
#include "shader.h"

namespace radi {
	namespace graphics {
		namespace ShaderFactory {

			RD_API Shader* DefaultShader();
			RD_API Shader* SimpleShader();
			RD_API Shader* BasicLightShader();

		}
	}
}