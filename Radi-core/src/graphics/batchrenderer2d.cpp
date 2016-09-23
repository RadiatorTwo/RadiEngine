#include "batchrenderer2d.h"

namespace radi
{
	namespace graphics
	{
		using namespace maths;

		BatchRenderer2D::BatchRenderer2D()
			: m_indexCount(0)
		{
			init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete m_IBO;
			glDeleteBuffers(1, &m_VBO);
			glDeleteVertexArrays(1, &m_VAO);
		}

		void BatchRenderer2D::init()
		{
			glGenVertexArrays(1, &m_VAO);
			glGenBuffers(1, &m_VBO);

			glBindVertexArray(m_VAO);
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			glBufferData(GL_ARRAY_BUFFER, RENDERER_BUFFER_SIZE, NULL, GL_DYNAMIC_DRAW);

			glEnableVertexAttribArray(SHADER_VERTEX_INDEX);
			glEnableVertexAttribArray(SHADER_UV_INDEX);
			glEnableVertexAttribArray(SHADER_MASK_UV_INDEX);
			glEnableVertexAttribArray(SHADER_TID_INDEX);
			glEnableVertexAttribArray(SHADER_MID_INDEX);
			glEnableVertexAttribArray(SHADER_COLOR_INDEX);

			glVertexAttribPointer(SHADER_VERTEX_INDEX, 3, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)0);
			glVertexAttribPointer(SHADER_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, uv)));
			glVertexAttribPointer(SHADER_MASK_UV_INDEX, 2, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mask_uv)));
			glVertexAttribPointer(SHADER_TID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, tid)));
			glVertexAttribPointer(SHADER_MID_INDEX, 1, GL_FLOAT, GL_FALSE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, mid)));
			glVertexAttribPointer(SHADER_COLOR_INDEX, 4, GL_UNSIGNED_BYTE, GL_TRUE, RENDERER_VERTEX_SIZE, (const GLvoid*)(offsetof(VertexData, color)));

			glBindBuffer(GL_ARRAY_BUFFER, 0);

			GLuint* indices = new GLuint[RENDERER_INDICES_SIZE];

			int offset = 0;
			for (int i = 0; i < RENDERER_INDICES_SIZE; i += 6)
			{
				indices[i] = offset + 0;
				indices[i + 1] = offset + 1;
				indices[i + 2] = offset + 2;

				indices[i + 3] = offset + 2;
				indices[i + 4] = offset + 3;
				indices[i + 5] = offset + 0;

				offset += 4;
			}

			m_IBO = new IndexBuffer(indices, RENDERER_INDICES_SIZE);

			glBindVertexArray(0);
		}

		float BatchRenderer2D::submitTexture(uint textureID)
		{
			float result = 0.0f;
			bool found = false;
			for (uint i = 0; i < m_textureSlots.size(); i++)
			{
				if (m_textureSlots[i] == textureID)
				{
					result = (float)(i + 1);
					found = true;
					break;
				}
			}

			if (!found)
			{
				if (m_textureSlots.size() >= RENDERER_MAX_TEXTURES)
				{
					end();
					flush();
					begin();
				}
				m_textureSlots.push_back(textureID);
				result = (float)(m_textureSlots.size());
			}
			return result;
		}

		float BatchRenderer2D::submitTexture(const Texture* texture)
		{
			return submitTexture(texture->getID());
		}

		void BatchRenderer2D::begin()
		{
			glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
			m_buffer = (VertexData*)glMapBuffer(GL_ARRAY_BUFFER, GL_WRITE_ONLY);
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable)
		{
			const maths::vec3& position = renderable->getPosition();
			const maths::vec2& size = renderable->getSize();
			const unsigned int color = renderable->getColor();
			const std::vector<maths::vec2>& uv = renderable->getUV();
			const GLuint tid = renderable->getTID();

			float ts = 0.0f;
			if (tid > 0)
				ts = submitTexture(renderable->getTexture());

			maths::mat4 maskTransform = maths::mat4::identity();
			const GLuint mid = m_mask ? m_mask->texture->getID() : 0;
			float ms = 0.0f;

			if (m_mask != nullptr)
			{
				maskTransform = mat4::invert(m_mask->transform);
				ms = submitTexture(m_mask->texture);
			}

			vec3 vertex = *m_transformationBack * position;
			m_buffer->vertex = vertex;
			m_buffer->uv = uv[0];
			m_buffer->mask_uv = maskTransform * vertex;
			m_buffer->tid = ts;
			m_buffer->mid = ms;
			m_buffer->color = color;
			m_buffer++;

			vertex = *m_transformationBack * vec3(position.x, position.y + size.y, position.z);
			m_buffer->vertex = vertex;
			m_buffer->uv = uv[1];
			m_buffer->mask_uv = maskTransform * vertex;
			m_buffer->tid = ts;
			m_buffer->mid = ms;
			m_buffer->color = color;
			m_buffer++;

			vertex = *m_transformationBack * vec3(position.x + size.x, position.y + size.y, position.z);
			m_buffer->vertex = vertex;
			m_buffer->uv = uv[2];
			m_buffer->mask_uv = maskTransform * vertex;
			m_buffer->tid = ts;
			m_buffer->mid = ms;
			m_buffer->color = color;
			m_buffer++;

			vertex = *m_transformationBack * vec3(position.x + size.x, position.y, position.z);
			m_buffer->vertex = vertex;
			m_buffer->uv = uv[3];
			m_buffer->mask_uv = maskTransform * vertex;
			m_buffer->tid = ts;
			m_buffer->mid = ms;
			m_buffer->color = color;
			m_buffer++;

			m_indexCount += 6;
		}

		void BatchRenderer2D::drawString(const std::string& text, const maths::vec3& position, const Font font, unsigned int color)
		{
			using namespace ftgl;

			float ts = 0.0f;
			ts = submitTexture(font.getID());

			const maths::vec2 scale = font.getScale();
			/*float scaleX = 960.0f / 32.0f;
			float scaleY = 540.0f / 18.0f;*/

			float x = position.x;

			texture_font_t* ft_font = font.getFTFont();

			for (uint i = 0; i < text.length(); i++)
			{
				char c = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(ft_font, c);
				if (glyph != NULL)
				{

					if (i > 0)
					{
						float kerning = texture_glyph_get_kerning(glyph, text[i - 1]);
						x += kerning / scale.x;
					}

					float x0 = x + glyph->offset_x / scale.x;
					float y0 = position.y + glyph->offset_y / scale.y;
					float x1 = x0 + glyph->width / scale.x;
					float y1 = y0 - glyph->height / scale.y;

					float u0 = glyph->s0;
					float v0 = glyph->t0;
					float u1 = glyph->s1;
					float v1 = glyph->t1;

					m_buffer->vertex = *m_transformationBack * maths::vec3(x0, y0, 0);
					m_buffer->uv = maths::vec2(u0, v0);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_transformationBack * maths::vec3(x0, y1, 0);
					m_buffer->uv = maths::vec2(u0, v1);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_transformationBack * maths::vec3(x1, y1, 0);
					m_buffer->uv = maths::vec2(u1, v1);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_transformationBack * maths::vec3(x1, y0, 0);
					m_buffer->uv = maths::vec2(u1, v0);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_indexCount += 6;

					x += glyph->advance_x / scale.x;
				}

			}
		}

		void BatchRenderer2D::end()
		{
			glUnmapBuffer(GL_ARRAY_BUFFER);
			glBindBuffer(GL_ARRAY_BUFFER, 0);
		}

		void BatchRenderer2D::flush()
		{
			for (uint i = 0; i < m_textureSlots.size(); i++)
			{
				glActiveTexture(GL_TEXTURE0 + i);
				glBindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
			}

			glBindVertexArray(m_VAO);
			m_IBO->bind();

			glDrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

			m_IBO->unbind();
			glBindVertexArray(0);

			m_indexCount = 0;
			m_textureSlots.clear();
		}
	}
}
