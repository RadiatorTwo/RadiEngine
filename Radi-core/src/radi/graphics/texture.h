#pragma once

#include "radi/radi_types.h"
#include "radi/radi_string.h"

namespace radi
{
	namespace graphics
	{
		enum class RD_API TextureWrap
		{
			REPEAT = 0x2901, // GL_REPEAT
			CLAMP = 0x2900, // GL_CLAMP
			MIRRORED_REPEAT = 0x8370, // GL_MIRRORED
			CLAMP_TO_EDGE = 0x812F, // GL_CLAMP_TO_EDGE
			CLAMP_TO_BORDER = 0x812D  // GL_CLAMP_TO_BORDER
		};

		enum class RD_API TextureFilter
		{
			LINEAR = 0x2601, // GL_LINEAR
			NEAREST = 0x2600  // GL_NEAREST
		};

		class RD_API Texture
		{
		private:
			static TextureWrap s_wrapMode;
			static TextureFilter s_filterMode;

			String m_name, m_filename;
			uint m_tID;
			uint m_width, m_height;
			unsigned int m_bits;
		public:
			Texture(uint width, uint height, uint bits = 24);
			Texture(const String& name, const String& filename);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const String& getName() const { return m_name; }
			inline const uint getID() const { return m_tID; }
			inline const uint getWidth() const { return m_width; }
			inline const uint getHeight() const { return m_height; }

			inline static void SetWrap(TextureWrap mode) { s_wrapMode = mode; }
			inline static void SetFilter(TextureFilter mode) { s_filterMode = mode; }
		private:
			uint load();
		};
	}
}