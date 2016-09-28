#include "radi/rd.h"
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

		Font* FontManager::get(const String& name)
		{
			for(Font* font : m_fonts)
			{
				if (font->GetName() == name)
				{
					return font;
				}
			}
			//TODO: Default Font statt null
			return nullptr;
		}

		Font* FontManager::get(const String& name, unsigned int size)
		{
			for (Font* font : m_fonts)
			{
				if (font->GetSize() == size && font->GetName() == name)
				{
					return font;
				}
			}
			//TODO: Default Font statt null
			return nullptr;
		}

		void FontManager::clean()
		{
			for (uint i = 0; i < m_fonts.size(); i++)
				delete m_fonts[i];
		}
	}
}