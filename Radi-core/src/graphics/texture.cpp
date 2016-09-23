#include "texture.h"

namespace radi
{
	namespace graphics
	{
		TextureWrap Texture::s_wrapMode = REPEAT;

		Texture::Texture(const std::string& name, const std::string& filename)
			:m_name(name), m_filename(filename)
		{
			m_tID = load();
		}

		Texture::~Texture()
		{
			glDeleteTextures(1, &m_tID);
		}


		GLuint Texture::load()
		{
			BYTE* pixels = load_image(m_filename.c_str(), &m_width, &m_height, &m_bits);

			GLuint result;
			glGenTextures(1, &result);
			glBindTexture(GL_TEXTURE_2D, result);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)s_wrapMode);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)s_wrapMode);

			if (m_bits != 24 && m_bits != 32)
				RADI_ERROR("[Texture] Unsupported image bit-depth! (%d)", m_bits);

			GLint internalFormat = m_bits == 32 ? GL_RGBA : GL_RGB;
			GLenum format = m_bits == 32 ?

				GL_BGRA : GL_BGR;

			glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, pixels);
			glBindTexture(GL_TEXTURE_2D, 0);

			delete[] pixels;

			return result;
		}

		void Texture::bind() const
		{
			glBindTexture(GL_TEXTURE_2D, m_tID);
		}

		void Texture::unbind() const
		{
			glBindTexture(GL_TEXTURE_2D, 0);
		}
	}
}
