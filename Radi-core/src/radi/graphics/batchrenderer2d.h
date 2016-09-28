#pragma once

#include "radi/rd.h"
#include "radi/common.h"
#include "radi/radi_types.h"

#include "renderer2d.h"
#include "renderable2d.h"
#include "Framebuffer.h"

#include "buffers/VertexArray.h"
#include "buffers/indexbuffer.h"

namespace radi
{
	namespace graphics
	{
#define RENDERER_MAX_SPRITES  60000
#define RENDERER_SPRITE_SIZE  RENDERER_VERTEX_SIZE * 4
#define RENDERER_BUFFER_SIZE  RENDERER_SPRITE_SIZE * RENDERER_MAX_SPRITES
#define RENDERER_INDICES_SIZE RENDERER_MAX_SPRITES * 6
#define RENDERER_MAX_TEXTURES 32 - 1

		class RD_API BatchRenderer2D : public Renderer2D
		{
		private:
			VertexArray* m_vertexArray;
			uint m_VAO;
			uint m_VBO;
			IndexBuffer* m_IBO;
			IndexBuffer* m_lineIBO;
			uint m_indexCount, m_lineIndexCount;
			VertexData* m_buffer;

			std::vector<uint> m_textureSlots;
			Framebuffer* m_framebuffer;
			Framebuffer* m_postEffectsBuffer;
			int m_screenBuffer;
			maths::tvec2<uint> m_viewportSize, m_screenSize;
			Shader* m_simpleShader;
			VertexArray* m_screenQuad;
		public:
			BatchRenderer2D(uint width, uint height);
			BatchRenderer2D(const maths::tvec2<uint>& screenSize);
			~BatchRenderer2D();

			void Begin() override;
			void submit(const Renderable2D* renderable) override;
			void drawAABB(const maths::AABB& aabb, uint color = 0xffffffff);
			void drawString(const String& text, const maths::vec3& position, const Font& font, unsigned int color) override;
			void end() override;
			void Present() override;

			inline void SetScreenSize(const maths::tvec2<uint>& size) { m_screenSize = size; }
			inline const maths::tvec2<uint>& GetScreenSize() const { return m_screenSize; }
			inline void SetViewportSize(const maths::tvec2<uint>& size) { m_viewportSize = size; }
			inline const maths::tvec2<uint>& GetViewportSize() const { return m_viewportSize; }

		private:
			void init();
			float submitTexture(uint textureID);
			float submitTexture(const Texture* texture);
		};
	}
}
