#pragma once

#include "Renderable2D.h"

namespace radi {
	namespace graphics {

		class RD_API Sprite : public Renderable2D
		{
		protected:
			Sprite();
		public:
			Sprite(API::Texture2D* texture);
			Sprite(float x, float y, API::Texture2D* texture);
			Sprite(float x, float y, float width, float height, uint color);
			Sprite(float x, float y, float width, float height, const maths::vec4& color);
			Sprite(float x, float y, float width, float height, API::Texture* texture);

			void SetUV(const std::vector<maths::vec2>& uv);

			inline void SetTexture(API::Texture2D* texture) { m_Texture = texture; }
		};

	}
}
