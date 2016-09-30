#include "radi/rd.h"
#include "Layer.h"

#include "radi/events/Events.h"
#include "radi/utils/Log.h"

namespace radi {
	namespace graphics {

		Layer::Layer()
			: m_Window(Window::GetWindowClass(nullptr)), m_Visible(true)
		{
		}

		Layer::~Layer()
		{
		}

		void Layer::Init()
		{
		}

		void Layer::OnEvent(events::Event& event)
		{
			events::EventDispatcher dispatcher(event);
			dispatcher.Dispatch<events::ResizeWindowEvent>([this](events::ResizeWindowEvent& e) { return OnResize(e.GetWidth(), e.GetHeight()); });
		}

		bool Layer::OnResize(uint width, uint height)
		{
			return false;
		}

		void Layer::OnTick()
		{
		}

		void Layer::OnUpdate()
		{
		}

		void Layer::OnRender()
		{
		}

	}
}