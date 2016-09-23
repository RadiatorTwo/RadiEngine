#include "texture_manager.h"

namespace radi {
	namespace graphics {

		std::vector<Texture*> TextureManager::m_textures;

		void TextureManager::add(Texture* texture)
		{
			m_textures.push_back(texture);
		}

		Texture* TextureManager::get(const std::string& name)
		{
			for (Texture* texture : m_textures)
			{
				if (texture->getName() == name)
					return texture;
			}
			return nullptr;
		}

		void TextureManager::clean()
		{
			for (uint i = 0; i < m_textures.size(); i++)
				delete m_textures[i];
		}

	}
}