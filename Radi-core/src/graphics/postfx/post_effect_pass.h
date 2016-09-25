#pragma once

#include "../Framebuffer.h"
#include "../shaders/Shader.h"

namespace radi {
	namespace graphics {

		class PostEffectsPass
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