#include "radi/rd.h"
#include "post_effects.h"

#include <radi/graphics/radi_render_api.h>

namespace radi {
	namespace graphics {

		PostEffects::PostEffects()
		{

		}

		PostEffects::~PostEffects()
		{

		}

		void PostEffects::Push(PostEffectsPass* pass)
		{
			m_Passes.push_back(pass);
		}

		void PostEffects::Pop()
		{
			m_Passes.pop_back();
		}

		void PostEffects::RenderPostEffects(Framebuffer* source, Framebuffer* target, VertexArray* quad, IndexBuffer* indices)
		{
			target->Bind();
			API::SetActiveTexture(GL_TEXTURE0);
			source->GetTexture()->bind();

			quad->Bind();
			indices->Bind();

			for (PostEffectsPass* pass : m_Passes)
				pass->RenderPass(target);

			indices->Unbind();
			quad->Unbind();
		}

	}
}