#include "post_effect_pass.h"

namespace radi {
	namespace graphics {

		PostEffectsPass::PostEffectsPass(Shader* shader)
			: m_shader(shader)
		{
			m_shader->bind();
			m_shader->setUniform1i("tex", 0);
			m_shader->unbind();
		}

		PostEffectsPass::~PostEffectsPass()
		{

		}

		void PostEffectsPass::RenderPass(Framebuffer* target)
		{
			m_shader->bind();
			m_shader->setUniformMat4("pr_matrix", maths::mat4::orthographic(0, target->GetWidth(), target->GetHeight(), 0, -1.0f, 1.0f));
			GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL));
			m_shader->unbind();
		}

	}
}