#pragma once

#include <utils/Log.h>
#include "../../ext/freetype-gl/freetype-gl.h"
#include "../maths/vec2.h"
#include <string>

namespace radi
{
	namespace graphics
	{
		class Font
		{
		private:
			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;
			float m_size;
			maths::vec2 m_scale;
			std::string m_name;
			std::string m_filename;
		public:
			Font(std::string name, std::string filename, float size);
			Font(const std::string& name, const byte* data, unsigned int datasize, float size);

			void setScale(float x, float y);

			inline ftgl::texture_font_t* getFTFont() const { return m_FTFont; }

			inline const int getID() const { return m_FTAtlas->id; }
			inline const maths::vec2 getScale() const { return m_scale; }
			inline const std::string getName() const { return m_name; }
			inline const std::string getFilename() const { return m_filename; }
			inline const float getSize() const { return m_size; }
		};
	}
}
