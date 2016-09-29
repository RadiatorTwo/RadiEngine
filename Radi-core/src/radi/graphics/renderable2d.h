#pragma once

#include "radi/common.h"
#include "radi/radi_types.h"

#include "renderer2d.h"
#include "texture.h"

#include "buffers/buffer.h"
#include "buffers/indexbuffer.h"
#include "shaders/shader.h"

#include "../maths/maths.h"

namespace radi
{
	namespace graphics
	{
		struct RD_API VertexData
		{
			maths::vec3 vertex;
			maths::vec2 uv;
			maths::vec2 mask_uv;
			float tid;
			float mid;
			unsigned int color;
		};

#define RENDERER_VERTEX_SIZE sizeof(VertexData)

		class RD_API Renderable2D
		{
		protected:
			maths::vec3 m_position;
			maths::vec2 m_size;
			uint m_Color;
			std::vector<maths::vec2> m_UVs;
			Texture* m_texture;
			bool m_Visible;
		protected:
			Renderable2D() : m_texture(nullptr) { m_UVs = GetDefaultUVs(); }
		public:
			Renderable2D(const maths::vec3& position, const maths::vec2& size, uint color)
				: m_position(position), m_size(size), m_Color(color), m_texture(nullptr), m_Visible(true)
			{
				m_UVs = GetDefaultUVs();
			}

			virtual ~Renderable2D() { }

			virtual void submit(Renderer2D* renderer) const
			{
				renderer->submit(this);
			}

			void setColor(unsigned int color) { m_Color = color; }
			void setColor(const maths::vec4& color)
			{
				uint r = (uint)(color.x * 255.0f);
				uint g = (uint)(color.y * 255.0f);
				uint b = (uint)(color.z * 255.0f);
				uint a = (uint)(color.w * 255.0f);

				m_Color = a << 24 | b << 16 | g << 8 | r;
			}

			inline const maths::vec3& getPosition() const { return m_position; }
			inline const maths::vec2& getSize() const { return m_size; }
			inline const unsigned int getColor() const { return m_Color; }
			inline const std::vector<maths::vec2>& GetUV() const { return m_UVs; }

			inline const uint getTID() const { return m_texture == nullptr ? 0 : m_texture->getID(); }
			inline const Texture* getTexture() const { return m_texture; }

			inline bool IsVisible() const { return m_Visible; }
			inline void SetVisible(bool visible) { m_Visible = visible; }
		public:
			static std::vector<maths::vec2> GetDefaultUVs()
			{
				static std::vector<maths::vec2> results;
				if (!results.size())
				{
					results.push_back(maths::vec2(0, 0));
					results.push_back(maths::vec2(0, 1));
					results.push_back(maths::vec2(1, 1));
					results.push_back(maths::vec2(1, 0));
				}
				return results;
			}
		};
	}
}
