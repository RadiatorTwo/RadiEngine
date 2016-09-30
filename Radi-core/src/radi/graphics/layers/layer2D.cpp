#include "radi/rd.h"
#include "Layer2D.h"

#include "../BatchRenderer2D.h"
#include "radi/app/Window.h"

namespace radi {
	namespace graphics {

		Layer2D::Layer2D(const maths::mat4& projectionMatrix)
			: m_Renderer(rdnew BatchRenderer2D(Window::GetWindowClass(nullptr)->GetWidth(), Window::GetWindowClass(nullptr)->GetHeight())), m_ProjectionMatrix(projectionMatrix)
		{
			m_Renderer->SetCamera(rdnew Camera(projectionMatrix));
			// m_Material = spnew Material(shader);
			// m_Material->SetUniform("sys_ProjectionMatrix", m_ProjectionMatrix);
		}

		Layer2D::~Layer2D()
		{
			rddel m_Material;
			rddel m_Renderer;

			for (uint i = 0; i < m_Renderables.size(); i++)
				rddel m_Renderables[i];
		}

		void Layer2D::Init()
		{
			OnInit(*m_Renderer, *m_Material);
		}

		void Layer2D::OnInit(Renderer2D& renderer, Material& material)
		{
		}

		Renderable2D* Layer2D::Add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
			return renderable;
		}

		Renderable2D* Layer2D::Submit(Renderable2D* renderable)
		{
			m_SubmittedRenderables.push_back(renderable);
			return renderable;
		}

		bool Layer2D::OnResize(uint width, uint height)
		{
			((BatchRenderer2D*)m_Renderer)->SetScreenSize(maths::tvec2<uint>(width, height));
			return false;
		}

		void Layer2D::OnRender()
		{
			m_Renderer->Begin();

			for (const Renderable2D* renderable : m_Renderables)
				renderable->Submit(m_Renderer);

			for (const Renderable2D* renderable : m_SubmittedRenderables)
				renderable->Submit(m_Renderer);

			m_Renderer->End();
			m_Renderer->Present();

			OnRender(*m_Renderer);

			m_SubmittedRenderables.clear();
		}

		void Layer2D::OnRender(Renderer2D& renderer)
		{
		}

	}
}