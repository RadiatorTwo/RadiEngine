#pragma once

#include "radi/Common.h"
#include "Sprite.h"
#include "font_manager.h"

namespace radi {
	namespace graphics {

		class RD_API Label : public Sprite
		{
		private:
			Font* m_Font;
		public:
			String text;
		public:
			Label(const String& text, float x, float y, uint color);
			Label(const String& text, float x, float y, Font* font, uint color);
			Label(const String& text, float x, float y, const String& font, uint color);
			Label(const String& text, float x, float y, const String& font, uint size, uint color);
			void Submit(Renderer2D* renderer) const override;
			void ValidateFont(const String& name, int32 size = -1);

			inline const Font& GetFont() const { return *m_Font; }
		};

	}
}