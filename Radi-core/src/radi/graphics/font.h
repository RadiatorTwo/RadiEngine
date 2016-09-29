#pragma once

#include "radi/common.h"
#include "radi/radi_types.h"
#include "../maths/vec2.h"
#include "radi/graphics/Texture.h"

namespace ftgl {
	struct texture_atlas_t;
	struct texture_font_t;
}

namespace radi
{
	namespace graphics
	{
		class RD_API Font
		{
		private:
			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;
			float m_size;
			maths::vec2 m_scale;
			String m_name;
			String m_filename;
			mutable Texture* m_Texture; // TODO: Replace with array
		public:
			Font(const String& name, const String& filename, float size);
			Font(const String& name, const byte* data, uint datasize, float size);

			void SetScale(float x, float y);
			uint GetID() const;

			inline void SetScale(const maths::vec2& scale) { m_scale = scale; }
			inline const maths::vec2& GetScale() const { return m_scale; }

			inline ftgl::texture_font_t* GetFTFont() const { return m_FTFont; }
			inline const String& GetName() const { return m_name; }
			inline const String& GetFileName() const { return m_filename; }
			inline float GetSize() const { return m_size; }

			Texture* GetTexture() const;
		};
	}
}
