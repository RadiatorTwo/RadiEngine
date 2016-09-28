#pragma once

#include "Mesh.h"

namespace radi {
	namespace graphics {

		struct RendererUniform
		{
			String uniform;
			byte* value;
		};

		struct RenderCommand
		{
			Mesh* mesh;
			std::vector<RendererUniform> uniforms;
		};

	}
}