#pragma once

#include "radi/graphics/renderer2D.h"
#include "radi/graphics/Label.h"
#include "radi/graphics/Sprite.h"

#include "radi/graphics/layers/layer2D.h"
#include "radi/graphics/shaders/shader.h"

#include "radi/events/events.h"
#include "radi/app/application.h"

#include "radi/rddebug/debug_menu.h"

namespace radi {
	namespace debug {

		class DebugLayer : public graphics::Layer2D
		{
		private:
			Application& m_application;
			graphics::Label* m_FPSLabel;
		public:
			DebugLayer();
			~DebugLayer();

			void OnInit(graphics::Renderer2D& renderer, graphics::Shader& shader) override;

			void OnTick() override;
			void OnUpdate() override;

			void OnEvent(events::Event& event) override;
			bool OnMouseMovedEvent(events::MouseMovedEvent& e);
			bool OnMousePressedEvent(events::MousePressedEvent& e);
			bool OnKeyPressedEvent(events::KeyPressedEvent& e);

			void OnRender(graphics::Renderer2D& renderer) override;
		};

	}
}
