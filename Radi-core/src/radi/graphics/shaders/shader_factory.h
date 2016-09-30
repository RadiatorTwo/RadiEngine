#pragma once

#include "radi/Common.h"
#include "Shader.h"

namespace radi {
	namespace graphics {
		namespace ShaderFactory {

			RD_API API::Shader* BatchRendererShader();
			RD_API API::Shader* SimpleShader();
			RD_API API::Shader* BasicLightShader();

			RD_API API::Shader* GeometryPassShader();

			RD_API API::Shader* DebugShader();

		}
	}
}