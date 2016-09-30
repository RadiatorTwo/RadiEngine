#pragma once

#include "radi/Common.h"
#include "Mesh.h"

namespace radi {
	namespace graphics {

		struct RD_API RendererUniform
		{
			String uniform;
			byte* value;
		};

		struct RD_API RenderCommand
		{
			Mesh* mesh;
			maths::mat4 transform;
			API::Shader* shader;
			std::vector<RendererUniform> uniforms;
		};

	}
}
