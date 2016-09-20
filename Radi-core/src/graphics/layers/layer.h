#pragma once

#include  "../renderer2d.h"
#include "../renderable2d.h"
#include "../../maths/maths.h"

namespace radi
{
	namespace graphics
	{
		using namespace radi::graphics;
		using namespace radi::maths;
		class Layer
		{
		protected:
			Renderer2D* m_renderer;
			std::vector<Renderable2D*> m_renderables;
			Shader* m_shader;
			mat4 m_projectionMatrix;
		protected:
			Layer(Renderer2D* renderer, Shader* shader, mat4 projectionMatrix);
		public:
			virtual ~Layer();
			virtual void add(Renderable2D* renderable);
			virtual void render();

			inline const std::vector<Renderable2D*>& getRenderables() { return m_renderables; }
		};

	}
}