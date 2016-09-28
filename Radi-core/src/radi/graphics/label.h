#pragma once

#include "radi/common.h"
#include "renderable2d.h"
#include "font_manager.h"

namespace radi {
	namespace graphics {

		class RD_API Label : public Renderable2D
		{
		public:
			Font* m_font;
			String text;
			maths::vec3& position;
			float x, y;
		public:
			Label(const String& text, float x, float y, uint color);
			Label(const String& text, float x, float y, Font* font, uint color);
			Label(const String& text, float x, float y, const String& font, uint color);
			Label(const String& text, float x, float y, const String& font, uint size, uint color);
			void submit(Renderer2D* renderer) const override;
			void validateFont(const String& name, int size = -1);
		};

	}
}