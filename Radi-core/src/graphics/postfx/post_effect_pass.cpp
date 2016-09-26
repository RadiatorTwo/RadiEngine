#include "post_effect_pass.h"

#include <graphics/radi_render_api.h>

namespace radi {
	namespace graphics {

		PostEffectsPass::PostEffectsPass(Shader* shader)
			: m_shader(shader)
		{
			m_shader->bind();
			m_shader->SetUniform1i("tex", 0);
			m_shader->unbind();
		}

		PostEffectsPass::~PostEffectsPass()
		{

		}

		void PostEffectsPass::RenderPass(Framebuffer* target)
		{
			m_shader->bind();
			m_shader->SetUniformMat4("pr_matrix", maths::mat4::orthographic(0, target->GetWidth(), target->GetHeight(), 0, -1.0f, 1.0f));
			API::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
			m_shader->unbind();
		}

	}
}