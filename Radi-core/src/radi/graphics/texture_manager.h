#pragma once

#include "radi/rd.h"
#include "radi/radi_types.h"
#include "radi/graphics/API/Texture.h"

namespace radi {
	namespace graphics {

		class RD_API TextureManager
		{
		private:
			static std::vector<API::Texture*> m_Textures;
		public:
			static API::Texture* Add(API::Texture* texture);
			static API::Texture* Get(const String& name);
			static void Clean();
		private:
			TextureManager() { }
		};

	}
}