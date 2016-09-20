#include "label.h"

namespace radi {
	namespace graphics {

		Label::Label(std::string text, float x, float y, maths::vec4 color)
			: Renderable2D(), text(text), position(m_position)
		{
			m_position = maths::vec3(x, y, 0.0f);
			m_color = color;
		}

		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(text, position, m_color);
		}

	}
}