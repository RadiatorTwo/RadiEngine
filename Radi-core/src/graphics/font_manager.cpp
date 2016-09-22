#include "font_manager.h"

namespace radi
{
	namespace graphics
	{
		std::vector<Font*> FontManager::m_fonts;

		void FontManager::add(Font* font)
		{
			m_fonts.push_back(font);
		}

		Font* FontManager::get()
		{
			return m_fonts[0];
		}

		Font* FontManager::get(const std::string& name)
		{
			for(Font* font : m_fonts)
			{
				if (font->getName() == name)
				{
					return font;
				}
			}
			//TODO: Default Font statt null
			return nullptr;
		}

		Font* FontManager::get(const std::string& name, unsigned int size)
		{
			for (Font* font : m_fonts)
			{
				if (font->getSize() == size && font->getName() == name)
				{
					return font;
				}
			}
			//TODO: Default Font statt null
			return nullptr;
		}

		void FontManager::clean()
		{
			for (int i = 0; i < m_fonts.size(); i++)
				delete m_fonts[i];
		}
		
		FontManager::FontManager()
		{
		}
	}
}