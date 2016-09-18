#pragma once
#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"
#include "renderer2d.h"
#include "../maths/maths.h"
#include "shader.h"


namespace radi
{
	namespace graphics
	{
		struct VertexData
		{
			maths::vec3 vertex;
			//maths::vec4 color;
			unsigned int color;
		};

		class Renderable2D
		{
		protected:
			maths::vec3 m_position;
			maths::vec2 m_size;
			maths::vec4 m_color;
		protected:
			Renderable2D() { }
		public:
			Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color)
				: m_position(position), m_size(size), m_color(color)
			{ }

			virtual ~Renderable2D() { }

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}

			inline const maths::vec3& getPosition() const { return m_position; }
			inline const maths::vec2& getSize() const { return m_size; }
			inline const maths::vec4& getColor() const { return m_color; }
		};
	}
}
