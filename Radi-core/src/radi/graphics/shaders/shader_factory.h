#pragma once

#include "Shader.h"

namespace radi {
	namespace graphics {
		namespace ShaderFactory {

			Shader* DefaultShader();
			Shader* SimpleShader();
			Shader* BasicLightShader();

		}
	}
}