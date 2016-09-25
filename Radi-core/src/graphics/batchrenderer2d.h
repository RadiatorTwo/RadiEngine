#pragma once

#include <cstddef>
#include <utils/Log.h>
#include <radi_types.h>
#include "renderer2d.h"
#include "renderable2d.h"
#include "Framebuffer.h"

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

		enum class RenderTarget
		{
			SCREEN = 0,
			BUFFER = 1
		};

		class BatchRenderer2D : public Renderer2D
		{

		private:
			GLuint m_VAO;
			GLuint m_VBO;
			IndexBuffer* m_IBO;
			GLsizei m_indexCount;
			VertexData* m_buffer;

			std::vector<GLuint> m_textureSlots;
			Framebuffer* m_framebuffer;
			int m_screenBuffer;
			maths::tvec2<uint> m_viewportSize, m_screenSize;
			Shader* m_simpleShader;
			uint m_screenQuad;
			RenderTarget m_target;
		public:
			BatchRenderer2D(const maths::tvec2<uint>& screenSize);
			~BatchRenderer2D();

			void begin() override;
			void submit(const Renderable2D* renderable) override;
			void drawString(const std::string& text, const maths::vec3& position, const Font& font, unsigned int color) override;
			void end() override;
			void flush() override;

			inline void SetScreenSize(const maths::tvec2<uint>& size) { m_screenSize = size; }
			inline const maths::tvec2<uint>& GetScreenSize() const { return m_screenSize; }
			inline void SetViewportSize(const maths::tvec2<uint>& size) { m_viewportSize = size; }
			inline const maths::tvec2<uint>& GetViewportSize() const { return m_viewportSize; }

			inline void SetRenderTarget(RenderTarget target) { m_target = target; }
			inline const RenderTarget GetRenderTarget() const { return m_target; }
		private:
			void init();
			float submitTexture(uint textureID);
			float submitTexture(const Texture* texture);
		};
	}
}
