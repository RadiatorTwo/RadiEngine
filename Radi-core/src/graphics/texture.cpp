#include "texture.h"

#include "utils/log.h"

namespace radi
{
	namespace graphics
	{
		TextureWrap Texture::s_wrapMode = REPEAT;

		Texture::Texture(uint width, uint height)
			: m_width(width), m_height(height), m_filename("NULL")
		{
			m_tID = load();
		}

		Texture::Texture(const std::string& name, const std::string& filename)
			: m_name(name), m_filename(filename)
		{
			m_tID = load();
		}

		Texture::~Texture()
		{
			GLCall(glDeleteTextures(1, &m_tID));
		}


		GLuint Texture::load()
		{
			BYTE* pixels = nullptr;
			if (m_filename != "NULL")
				 pixels = load_image(m_filename.c_str(), &m_width, &m_height, &m_bits);
			else
				 m_bits = 32; // Temporary

			GLuint result;
			GLCall(glGenTextures(1, &result));
			GLCall(glBindTexture(GL_TEXTURE_2D, result));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (GLint)s_wrapMode));
			GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (GLint)s_wrapMode));

			if (m_bits != 24 && m_bits != 32)
				RADI_ERROR("[Texture] Unsupported image bit-depth! (", m_bits, ")");

			GLint internalFormat = m_bits == 32 ? GL_RGBA : GL_RGB;
			GLenum format = m_bits == 32 ?

				GL_BGRA : GL_BGR;

			GLCall(glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, m_width, m_height, 0, format, GL_UNSIGNED_BYTE, pixels ? pixels : NULL));
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));

			if (pixels != nullptr)
				delete[] pixels;

			return result;
		}

		void Texture::bind() const
		{
			GLCall(glBindTexture(GL_TEXTURE_2D, m_tID));
		}

		void Texture::unbind() const
		{
			GLCall(glBindTexture(GL_TEXTURE_2D, 0));
		}
	}
}
