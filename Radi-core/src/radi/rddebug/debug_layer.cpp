#include "radi/rd.h"
#include "debug_layer.h"

#include "radi/maths/maths.h"
#include "radi/graphics/shaders/shader_factory.h"
#include "radi/graphics/label.h"
#include "radi/graphics/sprite.h"

#include "radi/embedded/Embedded.h"

namespace radi {
	namespace debug {

		using namespace maths;
		using namespace graphics;
		using namespace events;

		DebugLayer::DebugLayer()
			: Layer2D(ShaderFactory::DefaultShader(), mat4::Orthographic(0.0f, 32.0f, 0.0f, 18.0f, -1.0f, 1.0f)), m_application(Application::GetApplication())
		{
		}

		DebugLayer::~DebugLayer()
		{
		}

		void DebugLayer::OnInit(graphics::Renderer2D& renderer, graphics::Shader& shader)
		{
			renderer.SetRenderTarget(RenderTarget::SCREEN);
			m_FPSLabel = new Label("", 30.0f, 17.2f, FontManager::Get(24), 0xffffffff);
			Add(m_FPSLabel);
		}

		void DebugLayer::OnTick()
		{
			m_FPSLabel->text = std::to_string(m_application.GetFPS()) + " fps";

			RADI_INFO(m_application.GetUPS(), " ups, ", m_application.GetFPS(), " fps");
		}

		void DebugLayer::OnUpdate()
		{
			DebugMenu::Get()->OnUpdate();
		}

		void DebugLayer::OnEvent(Event& e)
		{
			EventDispatcher dispatcher(e);
			dispatcher.Dispatch<KeyPressedEvent>(METHOD(&DebugLayer::OnKeyPressedEvent));
			dispatcher.Dispatch<MousePressedEvent>(METHOD(&DebugLayer::OnMousePressedEvent));
			dispatcher.Dispatch<MouseReleasedEvent>(METHOD(&DebugLayer::OnMouseReleasedEvent));
			dispatcher.Dispatch<MouseMovedEvent>(METHOD(&DebugLayer::OnMouseMovedEvent));
		}

		bool DebugLayer::OnMousePressedEvent(events::MousePressedEvent& e)
		{
			return DebugMenu::IsVisible() ? DebugMenu::Get()->OnMousePressed(e) : false;
		}

		bool DebugLayer::OnMouseReleasedEvent(events::MouseReleasedEvent& e)
		{
			return DebugMenu::IsVisible() ? DebugMenu::Get()->OnMouseReleased(e) : false;
		}

		bool DebugLayer::OnKeyPressedEvent(KeyPressedEvent& e)
		{
			if (e.GetRepeat())
				return false;

			if (e.GetModifiers() == RD_MODIFIER_LEFT_CONTROL && e.GetKeyCode() == RD_KEY_TAB)
			{
				DebugMenu::SetVisible(!DebugMenu::IsVisible());
				return true;
			}
		}

		bool DebugLayer::OnMouseMovedEvent(MouseMovedEvent& e)
		{
			return false;
		}

		void DebugLayer::OnRender(graphics::Renderer2D& renderer)
		{
			if (DebugMenu::IsVisible())
				DebugMenu::Get()->OnRender(renderer);
		}

	}
}
