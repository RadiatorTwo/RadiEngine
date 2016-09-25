#pragma once

#include "renderable2d.h"
#include "font_manager.h"

namespace radi {
	namespace graphics {

		class Label : public Renderable2D
		{
		public:
			Font* m_font;
			std::string text;
			maths::vec3& position;
			float x, y;
		public:
			Label(const std::string& text, float x, float y, uint color);
			Label(const std::string& text, float x, float y, Font* font, uint color);
			Label(const std::string& text, float x, float y, const std::string& font, uint color);
			Label(const std::string& text, float x, float y, const std::string& font, uint size, uint color);
			void submit(Renderer2D* renderer) const override;
			void validateFont(const std::string& name, int size = -1);
		};

	}
}