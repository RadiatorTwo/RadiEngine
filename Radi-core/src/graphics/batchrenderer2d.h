#pragma once

#include <cstddef>
#include <utils/Log.h>
#include "renderer2d.h"
#include "renderable2d.h"
#include "buffers/indexbuffer.h"

namespace radi
{
	namespace graphics
	{
#define RENDERER_MAX_SPRITES  60000
#define RENDERER_VERTEX_SIZE  sizeof(VertexData)
#define RENDERER_SPRITE_SIZE  RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE  RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES 16

#define SHADER_VERTEX_INDEX 0
#define SHADER_UV_INDEX 1
#define SHADER_TID_INDEX 2
#define SHADER_COLOR_INDEX 3


		class BatchRenderer2D : public Renderer2D
		{

		private:
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer* m_IBO;
			GLsizei m_indexCount;
			VertexData* m_buffer;

			std::vector<GLuint> m_textureSlots;

		public:
			BatchRenderer2D();
			~BatchRenderer2D();
			void begin() override;
			void submit(const Renderable2D* renderable) override;
			void drawString(const std::string& text, const maths::vec3& position, const Font font, unsigned int color) override;
			void end() override;
			void flush() override;
		private:
			void init();
		};
	}
}
