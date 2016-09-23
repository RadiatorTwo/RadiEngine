#pragma once

#include <radi_types.h>
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
		public:
			Layer(Renderer2D* renderer, Shader* shader, mat4 projectionMatrix);
			virtual ~Layer();
			virtual Renderable2D* add(Renderable2D* renderable);

			inline void setMask(const Texture* mask) const { m_renderer->setMask(mask); }

			virtual void render();

			inline const std::vector<Renderable2D*>& getRenderables() { return m_renderables; }
		};

	}
}