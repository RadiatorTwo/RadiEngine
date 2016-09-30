#pragma once

#include "radi/graphics/API/Framebuffer.h"

namespace radi {
	namespace graphics {

		class RD_API GBuffer
		{
		public:
			enum class TextureType
			{
				Position = 0, Diffuse, Normal, TextureCoord
			};
		private:
			uint m_Framebuffer;
			uint m_Textures[4];
			uint m_DepthTexture;
			uint m_Width, m_Height;
		public:
			GBuffer(uint width, uint height);
			~GBuffer();

			void Bind(int32 mode = 0);
			void SetReadBuffer(TextureType type);

			inline uint GetWidth() const { return m_Width; }
			inline uint GetHeight() const { return m_Height; }

			inline uint GetTexture(uint index) const { return m_Textures[index]; }
		private:
			void Init();
		};

	}
}
