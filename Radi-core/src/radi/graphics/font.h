#pragma once

#include "radi/Common.h"
#include "radi/radi_types.h"
#include "radi/maths/vec2.h"
#include "radi/maths/rectangle.h"
#include "radi/graphics/API/texture2D.h"

namespace ftgl {
	struct texture_atlas_t;
	struct texture_font_t;
}

namespace radi {
	namespace graphics {

		class RD_API Font
		{
		private:
			ftgl::texture_atlas_t* m_FTAtlas;
			ftgl::texture_font_t* m_FTFont;
			float m_Size;
			maths::vec2 m_Scale;
			String m_Name;
			String m_Filename;
			mutable API::Texture2D* m_Texture; // TODO: Replace with array
		public:
			Font(const String& name, const String& filename, float size);
			Font(const String& name, const byte* data, uint datasize, float size);

			void SetScale(float x, float y);

			inline void SetScale(const maths::vec2& scale) { m_Scale = scale; }
			inline const maths::vec2& GetScale() const { return m_Scale; }

			inline ftgl::texture_font_t* GetFTFont() const { return m_FTFont; }
			inline const String& GetName() const { return m_Name; }
			inline const String& GetFileName() const { return m_Filename; }
			inline float GetSize() const { return m_Size; }

			maths::vec2 GetOffsets(const String& text) const;
			float GetWidth(const String& text) const;
			float GetHeight(const String& text) const;

			maths::Rectangle GetBounds(const String& text) const;

			API::Texture2D* GetTexture() const;
		private:
			void UpdateAtlas() const;
		};

	}
}