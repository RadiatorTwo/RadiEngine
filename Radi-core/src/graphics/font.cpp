#include "font.h"

#include <utils/Log.h>

namespace radi
{
	namespace graphics
	{
		Font::Font(const std::string name, const std::string filename, float size)
			: m_name(name), m_filename(filename), m_size(size), m_scale(maths::vec2(1.0f, 1.0f))
		{

			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTFont = ftgl::texture_font_new_from_file(m_FTAtlas, size, filename.c_str());
			RADI_ASSERT(m_FTFont, "Failed to load font '", filename.c_str(), "'!");
		}

		Font::Font(const std::string& name, const byte* data, unsigned int datasize, float size)
			: m_name(name), m_filename("NULL"), m_size(size), m_scale(maths::vec2(1.0f, 1.0f))
		{
			m_FTAtlas = ftgl::texture_atlas_new(512, 512, 2);
			m_FTFont = ftgl::texture_font_new_from_memory(m_FTAtlas, size, data, datasize);
			RADI_ASSERT(m_FTFont, "Failed to load font from data!");
		}

		void Font::setScale(float x, float y)
		{
			m_scale = maths::vec2(x, y);
		}
	}
}