#include "label.h"
#include "font_manager.h"

namespace radi {
	namespace graphics {
		
		Label::Label(std::string text, float x, float y, unsigned int color)
			: Renderable2D(), text(text), position(m_position), m_font(FontManager::get("SourceSansPro"))
		{
			m_position = maths::vec3(x, y, 0.0f);
			m_color = color;
		}

		Label::Label(std::string text, float x, float y, Font* font, unsigned int color)
			: Renderable2D(), text(text), position(m_position), m_font(font)
		{
			m_position = maths::vec3(x, y, 0.0f);
			m_color = color;
		}

		Label::Label(std::string text, float x, float y, const std::string& font, unsigned int color)
			: Renderable2D(), text(text), position(m_position), m_font(FontManager::get(font))
		{
			m_position = maths::vec3(x, y, 0.0f);
			m_color = color;

			validateFont(font);
		}

		Label::Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color)
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

		void Label::validateFont(const std::string& name, int size)
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
