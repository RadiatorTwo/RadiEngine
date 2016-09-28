#pragma once

#include "radi/common.h"

#include "../Framebuffer.h"
#include "../shaders/Shader.h"

namespace radi {
	namespace graphics {

		class RD_API PostEffectsPass
		{
		private:
			Shader* m_shader;
		public:
			PostEffectsPass(Shader* shader);
			~PostEffectsPass();

			void RenderPass(Framebuffer* target);
		};

	}
}