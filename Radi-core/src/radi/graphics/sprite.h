#pragma once

#include "renderable2d.h"

namespace radi
{
	namespace graphics
	{
		class RD_API Sprite : public Renderable2D
		{
		public:
			maths::vec3& position;
			maths::vec2& size;
		public:
			Sprite(Texture* texture);
			Sprite(float x, float y, Texture* texture);
			Sprite(float x, float y, float width, float height, uint color);
			Sprite(float x, float y, float width, float height, const maths::vec4& color);
			Sprite(float x, float y, float width, float height, Texture* texture);

			void setUV(const std::vector<maths::vec2>& uv);

			inline void SetTexture(Texture* texture) { m_texture = texture; }
		};
	}
}
