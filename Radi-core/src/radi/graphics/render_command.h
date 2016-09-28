#pragma once

#include "radi/rd.h"
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
			std::vector<RendererUniform> uniforms;
		};

	}
}