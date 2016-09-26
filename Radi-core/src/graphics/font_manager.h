#pragma once

#include <vector>
#include <radi_types.h>

#include "font.h"

namespace radi
{
	namespace graphics
	{
		class FontManager
		{
		private:
			static std::vector<Font*> m_fonts;
		public:
			static void add(Font* font);
			static Font* get();
			static Font* get(const String& name);
			static Font* get(const String& name, unsigned int size);
			static void clean();
		private:
			FontManager() {}
		};
	}
}
