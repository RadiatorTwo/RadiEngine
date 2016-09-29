#pragma once

#include "layer.h"

#include "radi/common.h"
#include "../../events/event.h"
#include "../renderable2d.h"
#include "../mask.h"

namespace radi {
	namespace graphics {

		class RD_API Layer2D : public Layer
		{
		private:
			Renderer2D* m_renderer;
		protected:
			std::vector<Renderable2D*> m_renderables;
			std::vector<Renderable2D*> m_SubmittedRenderables;
			Shader* m_shader;
			maths::mat4 m_projectionMatrix;
		public:
			// TODO: Replace Shader with Material!
			Layer2D(Shader* shader, const maths::mat4& projectionMatrix);
			virtual ~Layer2D();

			virtual void Init();
			virtual void OnInit(Renderer2D& renderer, Shader& shader);

			inline void SetMask(const Mask* mask) const { m_renderer->setMask(mask); }
			virtual Renderable2D* Add(Renderable2D* renderable);
			inline const std::vector<Renderable2D*>& GetRenderables() const { return m_renderables; }

			virtual Renderable2D* Submit(Renderable2D* renderable);

			virtual void OnRender(Renderer2D& renderer);
			void OnRender() override;
		};

	}
}