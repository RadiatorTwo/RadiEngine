#include "radi/rd.h"
#include "sprite.h"

namespace radi
{
	namespace graphics
	{
		Sprite::Sprite(Texture* texture)
			: Renderable2D(maths::vec3(0.0f, 0.0f, 0.0f), maths::vec2((float)texture->getWidth(), (float)texture->getHeight()), 0xffffffff), position(m_position), size(m_size)
		{
			m_texture = texture;
		}

		Sprite::Sprite(float x, float y, Texture* texture)
			: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2((float)texture->getWidth(), (float)texture->getHeight()), 0xffffffff), position(m_position), size(m_size)
		{
			m_texture = texture;
		}

		Sprite::Sprite(float x, float y, float width, float height, uint color)
			: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(width, height), color), position(m_position), size(m_size)
		{
		}

		Sprite::Sprite(float x, float y, float width, float height, const maths::vec4& color)
			: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(width, height), 0xffffffff), position(m_position), size(m_size)
		{
			setColor(color);
		}

		Sprite::Sprite(float x, float y, float width, float height, Texture* texture)
			: Renderable2D(maths::vec3(x, y, 0.0f), maths::vec2(width, height), 0xffffffff), position(m_position), size(m_size)
		{
			m_texture = texture;
		}

		void Sprite::setUV(const std::vector<maths::vec2>& uv)
		{
			m_UVs = uv;
		}
	}
}