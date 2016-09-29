#include "radi/rd.h"
#include "font_manager.h"

#include "radi/embedded/Embedded.h"

namespace radi
{
	namespace graphics
	{
		std::vector<Font*> FontManager::s_Fonts;
		maths::vec2 FontManager::s_Scale = maths::vec2(1, 1);

		void FontManager::SetScale(const maths::vec2& scale)
		{
			s_Scale = scale;
		}

		void FontManager::add(Font* font)
		{
			font->SetScale(s_Scale);
			s_Fonts.push_back(font);
		}

		Font* FontManager::get()
		{
			return s_Fonts[0];
		}

		Font* FontManager::get(const String& name)
		{
			for (Font* font : s_Fonts)
			{
				if (font->GetName() == name)
				{
					return font;
				}
			}
			//TODO: Default Font statt null
			return nullptr;
		}

		Font* FontManager::Get(uint size)
		{
			for (Font* font : s_Fonts)
			{
				if (font->GetSize() == size)
					return font;
			}
			Font* result = new Font("SourceSansPro", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, size);
			result->SetScale(s_Scale);
			add(result);
			return result;
		}

		Font* FontManager::Get(const String& name, uint size)
		{
			for (Font* font : s_Fonts)
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
			for (uint i = 0; i < s_Fonts.size(); i++)
				delete s_Fonts[i];
		}
	}
}