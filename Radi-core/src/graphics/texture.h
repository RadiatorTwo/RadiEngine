#pragma once

#include <iostream>
#include <string>

#include <FreeImage.h>

#include <radi_types.h>

#include "graphics/radi_render_api.h"

#include <utils/image_load.h>

namespace radi
{
	namespace graphics
	{
		enum class TextureWrap
		{
			REPEAT = GL_REPEAT,
			CLAMP = GL_CLAMP,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
		};

		enum class TextureFilter
		{
			LINEAR = GL_LINEAR,
			NEAREST = GL_NEAREST
		};

		class Texture
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
			inline const unsigned int getID() const { return m_tID; }
			inline const unsigned int getWidth() const { return m_width; }
			inline const unsigned int getHeight() const { return m_height; }

			inline static void SetWrap(TextureWrap mode) { s_wrapMode = mode; }
			inline static void SetFilter(TextureFilter mode) { s_filterMode = mode; }
		private:
			GLuint load();
		};
	}
}