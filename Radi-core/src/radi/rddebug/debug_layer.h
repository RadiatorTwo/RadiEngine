#pragma once

#include "radi/graphics/Renderer2D.h"
#include "radi/graphics/Label.h"
#include "radi/graphics/Sprite.h"

#include "radi/graphics/layers/Layer2D.h"
#include "radi/graphics/shaders/Shader.h"

#include "radi/events/Events.h"
#include "radi/app/Application.h"

#include "radi/rddebug/debug_menu.h"

#include "radi/graphics/Sprite.h"
#include "radi/graphics/API/Texture2D.h"

namespace radi {
	namespace debug {

		class RD_API DebugLayer : public graphics::Layer2D
		{
		private:
			static DebugLayer* s_Instance;
		private:
			Application& m_Application;
			graphics::Label* m_FPSLabel;
			graphics::Label* m_MemoryUsageLabel;
			graphics::Label* m_FrametimeLabel;
			std::vector<graphics::Sprite*> m_TempSprites;
		public:
			DebugLayer();
			~DebugLayer();

			void OnInit(graphics::Renderer2D& renderer, graphics::Material& material) override;

			void OnTick() override;
			void OnUpdate(const Timestep& ts) override;

			void OnEvent(events::Event& event) override;
			bool OnMouseMovedEvent(events::MouseMovedEvent& e);
			bool OnMousePressedEvent(events::MousePressedEvent& e);
			bool OnMouseReleasedEvent(events::MouseReleasedEvent& e);
			bool OnKeyPressedEvent(events::KeyPressedEvent& e);

			void OnRender(graphics::Renderer2D& renderer) override;

		public:
			inline static DebugLayer* GetInstance() { return s_Instance; }

			static void DrawSprite(graphics::Sprite* sprite);
			static void DrawTexture(graphics::API::Texture* texture, const maths::vec2& position = maths::vec2(), const maths::vec2& size = maths::vec2(8.0f, 8.0f));
		};

	}
}