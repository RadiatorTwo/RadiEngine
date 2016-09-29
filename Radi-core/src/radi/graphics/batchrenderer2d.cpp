#include "radi/rd.h"
#include "batchrenderer2d.h"

#include "shaders/shader_factory.h"
#include "mesh_factory.h"

#include "buffers/buffer.h"
#include "buffers/buffer_layout.h"

#include "radi/utils/log.h""

#include "radi_render_api.h"

#include <../freetype-gl/freetype-gl.h>

namespace radi
{
	namespace graphics
	{
		using namespace maths;

		BatchRenderer2D::BatchRenderer2D(uint width, uint height)
			: m_indexCount(0), m_screenSize(tvec2<uint>(width, height)), m_viewportSize(tvec2<uint>(width, height))
		{
			init();
		}

		BatchRenderer2D::BatchRenderer2D(const maths::tvec2<uint>& screenSize)
			: m_indexCount(0), m_screenSize(screenSize), m_viewportSize(screenSize)
		{
			init();
		}

		BatchRenderer2D::~BatchRenderer2D()
		{
			delete m_screenQuad;
			delete m_IBO;
			API::FreeBuffer(m_VBO);
			API::FreeVertexArray(m_VAO);
		}

		void BatchRenderer2D::init()
		{
			API::Buffer* buffer = new API::Buffer(GL_ARRAY_BUFFER, GL_DYNAMIC_DRAW);
			buffer->Bind();
			buffer->Resize(RENDERER_BUFFER_SIZE);

			buffer->layout.Push<vec3>("position");
			buffer->layout.Push<vec2>("uv");
			buffer->layout.Push<vec2>("mask_uv");
			buffer->layout.Push<float>("tid");
			buffer->layout.Push<float>("mid");
			buffer->layout.Push<byte>("color", 4, true);

			m_vertexArray = new VertexArray();
			m_vertexArray->Bind();
			m_vertexArray->PushBuffer(buffer);

			uint* indices = new uint[RENDERER_INDICES_SIZE];

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

			m_vertexArray->Unbind();

			// Setup Framebuffer
			m_screenBuffer = API::GetScreenBuffer();
			RADI_ASSERT(m_screenBuffer == 0);

			m_framebuffer = new Framebuffer(m_viewportSize);
			m_simpleShader = ShaderFactory::SimpleShader();
			m_simpleShader->Bind();
			m_simpleShader->SetUniformMat4("pr_matrix", maths::mat4::Orthographic(0, m_screenSize.x, m_screenSize.y, 0, -1.0f, 1.0f));
			m_simpleShader->SetUniform1i("tex", 0);
			m_simpleShader->Unbind();
			m_screenQuad = meshfactory::CreateQuad(0, 0, m_screenSize.x, m_screenSize.y);

			m_postEffects = new PostEffects();
			m_postEffectsBuffer = new Framebuffer(m_viewportSize);
		}

		float BatchRenderer2D::submitTexture(uint textureID)
		{
			if (!textureID)
				RADI_WARN("Invalid texture ID submitted!");

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
					Present();
					Begin();
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

		void BatchRenderer2D::Begin()
		{
			if (m_target == RenderTarget::BUFFER)
			{
				if (m_viewportSize != m_framebuffer->GetSize())
				{
					delete m_framebuffer;
					m_framebuffer = new Framebuffer(m_viewportSize);
					if (m_postEffectsEnabled)
					{
						delete m_postEffectsBuffer;
						m_postEffectsBuffer = new Framebuffer(m_viewportSize);
					}
				}

				if (m_postEffectsEnabled)
				{
					m_postEffectsBuffer->Bind();
					m_postEffectsBuffer->Clear();
				}

				m_framebuffer->Bind();
				m_framebuffer->Clear();

				glBlendFunc(GL_ONE, GL_ZERO);
			}
			else
			{
				API::BindFramebuffer(GL_FRAMEBUFFER, m_screenBuffer);
				API::SetViewport(0, 0, m_screenSize.x, m_screenSize.y);
			}

			m_vertexArray->GetBuffer()->Bind();
			m_buffer = m_vertexArray->GetBuffer()->GetPointer<VertexData>();
		}

		void BatchRenderer2D::submit(const Renderable2D* renderable)
		{
			if (!renderable->IsVisible())
				return;

			const vec3& position = renderable->getPosition();
			const vec2& size = renderable->getSize();
			const uint color = renderable->getColor();
			const std::vector<vec2>& uv = renderable->GetUV();
			const GLuint tid = renderable->getTID();

			float ts = 0.0f;
			if (tid > 0)
				ts = submitTexture(renderable->getTexture());

			mat4 maskTransform = mat4::Identity();
			const uint mid = m_mask ? m_mask->texture->getID() : 0;
			float ms = 0.0f;

			if (m_mask != nullptr)
			{
				maskTransform = mat4::Invert(m_mask->transform);
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

		void BatchRenderer2D::drawAABB(const maths::AABB& aabb, uint color)
		{
			// TODO: Draw 3D AABBs
#if 0
			m_DeferredLineVertexData.push_back({ aabb.min, vec2(), vec2(), 0, 0, color });
			m_DeferredLineVertexData.push_back({ vec3(aabb.min.x, aabb.max.y, 0.0f), vec2(), vec2(), 0, 0, color });

			m_DeferredLineVertexData.push_back({ vec3(aabb.min.x, aabb.max.y, 0.0f), vec2(), vec2(), 0, 0, color });
			m_DeferredLineVertexData.push_back({ aabb.max, vec2(), vec2(), 0, 0, color });

			m_DeferredLineVertexData.push_back({ aabb.max, vec2(), vec2(), 0, 0, color });
			m_DeferredLineVertexData.push_back({ vec3(aabb.max.x, aabb.min.y, 0.0f), vec2(), vec2(), 0, 0, color });

			m_DeferredLineVertexData.push_back({ vec3(aabb.max.x, aabb.min.y, 0.0f), vec2(), vec2(), 0, 0, color });
			m_DeferredLineVertexData.push_back({ aabb.min, vec2(), vec2(), 0, 0, color });
#endif
		}

		void BatchRenderer2D::DrawString(const String& text, const maths::vec3& position, const Font& font, uint color)
		{
			using namespace ftgl;

			float ts = 0.0f;
			ts = submitTexture(font.GetID());

			const maths::vec2& scale = font.GetScale();

			float x = position.x;

			texture_font_t* ftFont = font.GetFTFont();

			for (uint i = 0; i < text.length(); i++)
			{
				char c = text[i];
				texture_glyph_t* glyph = texture_font_get_glyph(ftFont, c);
				if (glyph)
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

					m_buffer->vertex = *m_transformationBack * vec3(x0, y0, 0);
					m_buffer->uv = vec2(u0, v0);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_transformationBack * vec3(x0, y1, 0);
					m_buffer->uv = vec2(u0, v1);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_transformationBack * vec3(x1, y1, 0);
					m_buffer->uv = vec2(u1, v1);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_buffer->vertex = *m_transformationBack * vec3(x1, y0, 0);
					m_buffer->uv = vec2(u1, v0);
					m_buffer->tid = ts;
					m_buffer->color = color;
					m_buffer++;

					m_indexCount += 6;

					x += glyph->advance_x / scale.x;
				}

			}
		}

		void BatchRenderer2D::FillRect(float x, float y, float width, float height, uint color)
		{
			vec3 position(x, y, 0.0f);
			vec2 size(width, height);
			const std::vector<vec2>& uv = Renderable2D::GetDefaultUVs();
			float ts = 0.0f;
			mat4 maskTransform = mat4::Identity();
			uint mid = m_mask ? m_mask->texture->getID() : 0;

			float ms = 0.0f;
			if (m_mask != nullptr)
			{
				maskTransform = mat4::Invert(m_mask->transform);
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

		void BatchRenderer2D::end()
		{
			m_vertexArray->GetBuffer()->ReleasePointer();
			m_vertexArray->GetBuffer()->Unbind();
		}

		void BatchRenderer2D::Present()
		{
			GLCall(glDepthFunc(GL_NEVER));
			GLCall(glDisable(GL_DEPTH_TEST));

			for (uint i = 0; i < m_textureSlots.size(); i++)
			{
				API::SetActiveTexture(GL_TEXTURE0 + i);
				API::BindTexture(GL_TEXTURE_2D, m_textureSlots[i]);
			}

			// Draw buffers here
			{
				m_vertexArray->Bind();
				m_IBO->Bind();

				API::DrawElements(GL_TRIANGLES, m_indexCount, GL_UNSIGNED_INT, NULL);

				m_IBO->Unbind();
				m_vertexArray->Unbind();
			}

			m_indexCount = 0;
			m_textureSlots.clear();

			if (m_target == RenderTarget::BUFFER)
			{
				// Post Effects pass should go here!
				if (m_postEffectsEnabled)
					m_postEffects->RenderPostEffects(m_framebuffer, m_postEffectsBuffer, m_screenQuad, m_IBO);

				// Display Framebuffer - potentially move to Framebuffer class
				API::BindFramebuffer(GL_FRAMEBUFFER, m_screenBuffer);
				API::SetViewport(0, 0, m_screenSize.x, m_screenSize.y);
				glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
				m_simpleShader->Bind();

				API::SetActiveTexture(GL_TEXTURE0);

				if (m_postEffectsEnabled)
					m_postEffectsBuffer->GetTexture()->bind();
				else
					m_framebuffer->GetTexture()->bind();

				m_screenQuad->Bind();

				m_IBO->Bind();
				API::DrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, NULL);
				m_IBO->Unbind();
				m_screenQuad->Unbind();
				m_simpleShader->Unbind();
			}
		}
	}
}
