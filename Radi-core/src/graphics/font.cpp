#include "font.h"

namespace radi
{
	namespace graphics
	{
		Font::Font(std::string name, std::string filename, float size)
			: m_name(name),m_filename(filename),m_size(size), m_scale(maths::vec2(1, 1))
		{

			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, size, m_filename.c_str());
			RADI_ASSERT(m_FTFont, "Failed to load font '", filename.c_str(), "'!");
		}


		void Font::setScale(float x, float y)
		{
			m_scale = maths::vec2(x, y);
		}
	}
}