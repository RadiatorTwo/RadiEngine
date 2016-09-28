#include "radi/rd.h"
#include "Layer2D.h"

#include "../batchrenderer2d.h"
#include "../window.h"

namespace radi {
	namespace graphics {

		Layer2D::Layer2D(Shader* shader, const maths::mat4& projectionMatrix)
			: m_renderer(new BatchRenderer2D(Window::GetWindowClass(nullptr)->GetWidth(), Window::GetWindowClass(nullptr)->GetHeight())), m_shader(shader), m_projectionMatrix(projectionMatrix)
		{
			m_shader->Bind();
			m_shader->SetUniformMat4("pr_matrix", m_projectionMatrix);

			int texIDs[] =
			{
				0, 1, 2, 3, 4, 5, 6, 7, 8, 9,
				10, 11, 12, 13, 14, 15, 16, 17, 18, 19,
				20, 21, 22, 23, 24, 25, 26, 27, 28, 29,
				30, 31
			};

			m_shader->SetUniform1iv("textures", texIDs, 32);
			m_shader->Unbind();
		}

		Layer2D::~Layer2D()
		{
			delete m_shader;
			delete m_renderer;

			for (uint i = 0; i < m_renderables.size(); i++)
				delete m_renderables[i];
		}

		void Layer2D::Init()
		{
			OnInit(*m_renderer, *m_shader);
		}

		void Layer2D::OnInit(Renderer2D& renderer, Shader& shader)
		{
		}

		Renderable2D* Layer2D::Add(Renderable2D* renderable)
		{
			m_renderables.push_back(renderable);
			return renderable;
		}

		void Layer2D::OnRender()
		{
			m_shader->Bind();
			m_renderer->Begin();

			for (const Renderable2D* renderable : m_renderables)
				renderable->submit(m_renderer);

			m_renderer->end();
			m_renderer->Present();

			OnRender(*m_renderer);
		}

		void Layer2D::OnRender(Renderer2D& renderer)
		{
		}

	}
}