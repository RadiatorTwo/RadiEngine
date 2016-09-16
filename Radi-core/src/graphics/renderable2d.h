#pragma once
#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "buffers/vertexarray.h"

#include "../maths/maths.h"
#include "shader.h"

namespace radi
{
	namespace graphics
	{
		class Renderable2D
		{
		protected:
			maths::vec3 m_position;
			maths::vec2 m_size;
			maths::vec4 m_color;

			VertexArray* m_vertexArray;
			IndexBuffer* m_indexBuffer;
			GLushort* m_indices;
			Shader* m_shader;
		public:
			Renderable2D(maths::vec3 position, maths::vec2 size, maths::vec4 color, Shader* shader)
				: m_position(position), m_size(size), m_color(color), m_shader(shader)
			{
				m_vertexArray = new VertexArray();
				GLfloat vertices[] =
				{
					0, 0, 0,
					0, size.y, 0,
					size.x, size.y, 0,
					size.x, 0, 0
				};

				GLfloat colors[] =
				{
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w,
					color.x, color.y, color.z, color.w
				};

				m_vertexArray->addBuffer(new Buffer(vertices, 4 * 3, 3), 0);
				m_vertexArray->addBuffer(new Buffer(colors, 4 * 4, 4), 1);

				m_indices = new GLushort[6]{ 0,1,2,2,3,0 };
				m_indexBuffer = new IndexBuffer(m_indices, 6);
			}

			virtual ~Renderable2D()
			{
				delete m_vertexArray;
				delete m_indexBuffer;
			}

			inline const VertexArray* getVAO() const { return m_vertexArray; }
			inline const IndexBuffer* getIBO() const { return m_indexBuffer; }
			inline const GLushort* getIndices() const { return m_indices; }

			inline Shader* getShader() const { return m_shader; }

			const maths::vec3& getPosition() const { return m_position; }
			const maths::vec2& getSize() const { return m_size; }
			const maths::vec4& getColor() const { return m_color; }
		};
	}
}
