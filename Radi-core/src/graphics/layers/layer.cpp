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

		bool Layer::OnEvent(const events::Event& event)
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
