#pragma once

#include "radi/rd.h"
#include "radi/Common.h"

#include "radi/graphics/API/Framebuffer.h"
#include "radi/graphics/API/VertexArray.h"
#include "radi/graphics/API/IndexBuffer.h"
#include "post_effect_pass.h"

namespace radi {
	namespace graphics {

		// The Post Effects pipeline
		class RD_API PostEffects
		{
		private:
			std::vector<PostEffectsPass*> m_Passes;
		public:
			PostEffects();
			~PostEffects();
			void Push(PostEffectsPass* pass);
			void Pop();

			void RenderPostEffects(Framebuffer* source, Framebuffer* target, API::VertexArray* quad, API::IndexBuffer* indices);
		};

	}
}