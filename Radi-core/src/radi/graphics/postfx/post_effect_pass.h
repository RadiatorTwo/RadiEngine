#pragma once

#include "radi/Common.h"
#include "radi/graphics/API/Framebuffer.h"
#include "../Material.h"

namespace radi {
	namespace graphics {

		class RD_API PostEffectsPass
		{
		private:
			Material* m_Material;
		public:
			PostEffectsPass(API::Shader* shader);
			~PostEffectsPass();

			void RenderPass(Framebuffer* target);
		};

	}
}