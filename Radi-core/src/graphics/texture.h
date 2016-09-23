#pragma once

#include <iostream>
#include <string>
#include <utils/log.h>
#include <radigl.h>
#include <FreeImage.h>
#include "utils/image_load.h"


namespace radi
{
	namespace graphics
	{
		class Texture
		{
		private:
			std::string m_name, m_filename;
			GLuint m_tID;
			GLsizei m_width, m_height;
			unsigned int m_bits;
		public:
			Texture(const std::string& name, const std::string& filename);
			~Texture();
			void bind() const;
			void unbind() const;

			inline const std::string& getName() const { return m_name; }
			inline const unsigned int getID() { return m_tID; }
			inline const unsigned int getWidth() { return m_width; }
			inline const unsigned int getHeight() { return m_height; }

		private:
			GLuint load();
		};
	}
}