#pragma once

#include <iostream>
#include <string>

#include <FreeImage.h>

#include <radi_types.h>
#include <radigl.h>

#include <utils/image_load.h>

namespace radi
{
	namespace graphics
	{
		enum TextureWrap
		{
			REPEAT = GL_REPEAT,
			CLAMP = GL_CLAMP,
			MIRRORED_REPEAT = GL_MIRRORED_REPEAT,
			CLAMP_TO_EDGE = GL_CLAMP_TO_EDGE,
			CLAMP_TO_BORDER = GL_CLAMP_TO_BORDER
		};

		class Texture
		{
		private:
			static TextureWrap s_wrapMode;

			std::string m_name, m_filename;
			uint m_tID;
			uint m_width, m_height;
			unsigned int m_bits;
		public:
			Texture(uint width, uint height);
			Texture(const std::string& name, const std::string& filename);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const std::string& getName() const { return m_name; }
			inline const unsigned int getID() const { return m_tID; }
			inline const unsigned int getWidth() const { return m_width; }
			inline const unsigned int getHeight() const { return m_height; }

			inline static void SetWrap(TextureWrap mode) { s_wrapMode = mode; }
		private:
			GLuint load();
		};
	}
}