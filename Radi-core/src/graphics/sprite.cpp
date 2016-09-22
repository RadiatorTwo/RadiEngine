#include "sprite.h"

namespace radi
{
	namespace graphics
	{
		Sprite::Sprite(float x, float y, float width, float height, unsigned int color)
			:Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), color), position(m_position)
		{

		}

		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
			: Renderable2D(maths::vec3(x, y, 0), maths::vec2(width, height), 0xffffffff), position(m_position)
		{
			m_texture = texture;
		}
	}
}