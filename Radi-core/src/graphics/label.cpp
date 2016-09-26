#include "label.h"
#include "font_manager.h"

namespace radi {
	namespace graphics {
		
		Label::Label(const String& text, float x, float y, uint color)
			: Renderable2D(), text(text), position(m_position), m_font(FontManager::get("SourceSansPro"))
		{
			m_position = maths::vec3(x, y, 0.0f);
			m_color = color;
		}

		Label::Label(const String& text, float x, float y, Font* font, uint color)
			: Renderable2D(), text(text), position(m_position), m_font(font)
		{
			m_position = maths::vec3(x, y, 0.0f);
			m_color = color;
		}

		Label::Label(const String& text, float x, float y, const String& font, uint color)
			: Renderable2D(), text(text), position(m_position), m_font(FontManager::get(font))
		{
			m_position = maths::vec3(x, y, 0.0f);
			m_color = color;

			validateFont(font);
		}

		Label::Label(const String& text, float x, float y, const String& font, uint size, uint color)
			: Renderable2D(), text(text), position(m_position), m_font(FontManager::get(font, size))
		{
			m_position = maths::vec3(x, y, 0.0f);
			m_color = color;

			validateFont(font, size);
		}

		void Label::submit(Renderer2D* renderer) const
		{
			renderer->drawString(text, position, *m_font, m_color);
		}

		void Label::validateFont(const String& name, int size)
		{
			if (m_font != nullptr)
				return;

			std::cout << "NULL FONT! Font=" << name;
			if (size > 0)
				std::cout << ", Size=" << size;
			std::cout << std::endl;

			m_font = FontManager::get("SourceSansPro");
		}

	}
}
