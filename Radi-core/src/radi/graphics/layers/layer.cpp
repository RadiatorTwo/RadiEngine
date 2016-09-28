#include "radi/rd.h"
#include "layer.h"

namespace radi
{
	namespace graphics
	{
		Layer::Layer() : m_window(Window::GetWindowClass(nullptr))
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
