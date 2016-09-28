#include "layer3D.h"

#include "../forward_renderer.h"

namespace radi {
	namespace graphics {

		Layer3D::Layer3D(Scene* scene)
			: m_scene(scene), m_renderer(new ForwardRenderer())
		{
		}

		Layer3D::~Layer3D()
		{
			delete m_scene;
			delete m_renderer;
		}

		void Layer3D::Init()
		{
			OnInit(*m_renderer, *m_scene);
		}

		void Layer3D::OnInit(Renderer3D& renderer, Scene& scene)
		{
		}

		void Layer3D::OnRender()
		{
			OnRender(*m_renderer);
		}

		void Layer3D::OnRender(Renderer3D& renderer)
		{
			m_scene->Render(renderer);
			renderer.Present();
		}

	}
}