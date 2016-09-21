#pragma once

#include "renderable2d.h"

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
			Label(std::string text, float x, float y, unsigned int color);
			Label(std::string text, float x, float y, Font* font, unsigned int color);
			Label(std::string text, float x, float y, const std::string& font, unsigned int color);
			Label(std::string text, float x, float y, const std::string& font, unsigned int size, unsigned int color);
			void submit(Renderer2D* renderer) const override;
			void validateFont(const std::string font, int size = -1);
		};

	}
}