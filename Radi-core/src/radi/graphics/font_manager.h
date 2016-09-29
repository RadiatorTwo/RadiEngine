#pragma once


#include "radi/rd.h"
#include "radi/common.h"
#include "radi/radi_types.h"

#include "font.h"

namespace radi
{
	namespace graphics
	{
		class RD_API FontManager
		{
		private:
			static std::vector<Font*> s_Fonts;
			static maths::vec2 s_Scale;
		public:
			static void SetScale(const maths::vec2& scale);

			static void add(Font* font);
			static Font* get();
			static Font* get(const String& name);
			static Font* Get(uint size);
			static Font* Get(const String& name, uint size);
			static void clean();
		private:
			FontManager() {}
		};
	}
}
