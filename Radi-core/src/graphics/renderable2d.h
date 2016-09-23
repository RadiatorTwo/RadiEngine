#pragma once

#include <radi_types.h>

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

#include "renderer2d.h"
#include "texture.h"

#include "../maths/maths.h"
#include "shaders/shader.h"

namespace radi
{
	namespace graphics
	{
		struct VertexData
		{
			maths::vec3 vertex;
			maths::vec2 uv;
			maths::vec2 mask_uv;
			float tid;
			float mid;
			unsigned int color;
		};

		class Renderable2D
		{
		protected:
			maths::vec3 m_position;
			maths::vec2 m_size;
			unsigned int m_color;
			std::vector<maths::vec2> m_uv;
			Texture* m_texture;
		protected:
			Renderable2D() :m_texture(nullptr) { setUVDefaults(); }
		public:
			Renderable2D(maths::vec3 position, maths::vec2 size, unsigned int color)
				: m_position(position), m_size(size), m_color(color), m_texture(nullptr)
			{
				setUVDefaults();
			}

			virtual ~Renderable2D() { }

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}

			void setColor(unsigned int color) { m_color = color; }
			void setColor(const maths::vec4& color)
			{
				uint r = (uint)(color.x * 255.0f);
				uint g = (uint)(color.y * 255.0f);
				uint b = (uint)(color.z * 255.0f);
				uint a = (uint)(color.w * 255.0f);

				m_color = a << 24 | b << 16 | g << 8 | r;
			}

			inline const maths::vec3& getPosition() const { return m_position; }
			inline const maths::vec2& getSize() const { return m_size; }
			inline const unsigned int getColor() const { return m_color; }
			inline const std::vector<maths::vec2>& getUV() const { return m_uv; }

			inline const GLuint getTID() const { return m_texture == nullptr ? 0 : m_texture->getID(); }
			inline const Texture* getTexture() const { return m_texture; }
		private:
			void setUVDefaults()
			{
				m_uv.push_back(maths::vec2(0, 0));
				m_uv.push_back(maths::vec2(0, 1));
				m_uv.push_back(maths::vec2(1, 1));
				m_uv.push_back(maths::vec2(1, 0));
			}
		};
	}
}
