#pragma once

#include "radi/rd.h"
#include <radi/radi_types.h>
#include "radi/graphics/texture.h"

namespace radi {
	namespace graphics {

		class RD_API TextureManager
		{
		private:
			static std::vector<Texture*> m_textures;
		public:
			static void add(Texture* texture);
			static Texture* get(const String& name);
			static void clean();
		private:
			TextureManager() { }
		};

	}
}