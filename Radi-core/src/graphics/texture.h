#pragma once

#include <FreeImage.h>
#include <string>
#include <GL/glew.h>
#include "../utils/image_load.h"

namespace radi
{
	namespace graphics
	{
		class Texture
		{
		private:
			std::string m_filename;
			GLuint m_tID;
			GLsizei m_width, m_height;
		public:
			Texture(const std::string& filename);
			~Texture();
			void bind() const;
			void unbind() const;
			
			inline const unsigned int getWidth() { return m_width; }
			inline const unsigned int getHeight() { return m_height; }

		private:
			GLuint load();
		};
	}
}