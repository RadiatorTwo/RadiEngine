#pragma once

#include <vector>

#include "../framebuffer.h"
#include "../buffers/vertexarray.h"
#include "../buffers/indexbuffer.h"
#include "post_effect_pass.h"

namespace radi {
	namespace graphics {

		// The Post Effects pipeline
		class PostEffects
		{
		private:
			std::vector<PostEffectsPass*> m_Passes;
		public:
			PostEffects();
			~PostEffects();
			void Push(PostEffectsPass* pass);
			void Pop();

			void RenderPostEffects(Framebuffer* source, Framebuffer* target, VertexArray* quad, IndexBuffer* indices);
		};

	}
}