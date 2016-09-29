#include "radi/rd.h"
#include "texture.h"

#include <GL/glew.h>
#include <FreeImage.h>

#include "radi/utils/image_load.h"
#include "radi_render_api.h"

namespace radi
{
	namespace graphics
	{
		TextureWrap Texture::s_wrapMode = TextureWrap::REPEAT;
		TextureFilter Texture::s_filterMode = TextureFilter::LINEAR;

		Texture::Texture(uint width, uint height, uint bits)
			: m_width(width), m_height(height), m_bits(bits), m_filename("NULL")
		{
			m_tID = load();
		}

		Texture::Texture(const String& name, const String& filename)
			: m_name(name), m_filename(filename)
		{
			m_tID = load();
		}
		
		Texture::Texture(uint glID)
			: m_name(std::to_string(glID)), m_filename("NULL")
		{
			m_tID = glID;
		}

		Texture::~Texture()
		{
			API::FreeTexture(m_tID);
		}

		GLuint Texture::load()
		{
			BYTE* pixels = nullptr;
			if (m_filename != "NULL")
				pixels = load_image(m_filename.c_str(), &m_width, &m_height, &m_bits);

			uint result = API::CreateTexture();
			API::BindTexture(GL_TEXTURE_2D, result);
			API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, (int)s_filterMode);
			API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, (int)s_filterMode);
			API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, (int)s_wrapMode);
			API::SetTextureParameter(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, (int)s_wrapMode);

			if (m_bits != 24 && m_bits != 32)
				RADI_ERROR("[Texture] Unsupported image bit-depth! (", m_bits, ")");

			int internalFormat = m_bits == 32 ? GL_RGBA : GL_RGB;
			uint format = m_bits == 32 ?

				GL_BGRA : GL_BGR;

			API::SetTextureData(GL_TEXTURE_2D, internalFormat, m_width, m_height, format, GL_UNSIGNED_BYTE, pixels ? pixels : NULL);
			API::UnbindTexture(GL_TEXTURE_2D);

			if (pixels != nullptr)
				delete[] pixels;

			return result;
		}

		void Texture::bind() const
		{
			API::BindTexture(GL_TEXTURE_2D, m_tID);
		}

		void Texture::unbind() const
		{
			API::UnbindTexture(GL_TEXTURE_2D);
		}
	}
}
