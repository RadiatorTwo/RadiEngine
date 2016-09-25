#include "layer.h"

namespace radi
{
	namespace graphics
	{
		Layer::Layer(Renderer2D* renderer, Shader* shader, mat4 projectionMatrix)
			:renderer(renderer), m_shader(shader), m_projectionMatrix(projectionMatrix)
		{
			m_shader->bind();
			m_shader->setUniformMat4("pr_matrix", m_projectionMatrix);

			GLint textIDs[] =
			{
				 0,  1,  2,  3,  4,  5,  6,  7,  8,  9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};

			m_shader->setUniform1iv("textures", 32, textIDs);

			m_shader->unbind();
		}

		Layer::~Layer()
		{
			delete m_shader;
			delete renderer;

			for (uint i = 0; i < m_renderables.size(); i++)
			{
				delete m_renderables[i];
			}
		}

		Renderable2D* Layer::add(Renderable2D* renderable)
		{
			m_renderables.push_back(renderable);
			return renderable;
		}

		void Layer::render()
		{
			m_shader->bind();
			renderer->begin();

			for (const Renderable2D* renderable : m_renderables)
			{
				renderable->submit(renderer);
			}
			
			renderer->end();

			renderer->flush();
			//m_shader->disable();
		}
	}
}
