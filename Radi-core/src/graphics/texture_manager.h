#pragma once

#include <vector>
#include <radi_types.h>
#include "texture.h"

namespace radi {
	namespace graphics {

		class TextureManager
		{
		private:
			static std::vector<Texture*> m_textures;
		public:
			static void add(Texture* texture);
			static Texture* get(const std::string& name);
			static void clean();
		private:
			TextureManager() { }
		};

	}
}