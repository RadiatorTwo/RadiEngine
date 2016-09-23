#pragma once

#include <radigl.h>
#include <vector>
#include "font.h"
#include "texture.h"
#include "Mask.h"
#include "../maths/maths.h"


namespace radi
{
	namespace graphics
	{
		class Renderable2D;

		class Renderer2D
		{
		protected:
			std::vector<maths::mat4> m_transformationStack;
			const maths::mat4* m_transformationBack;
			const Mask* m_mask;
		protected:
			Renderer2D() : m_mask(nullptr)
			{
				m_transformationStack.push_back(maths::mat4::identity());
				m_transformationBack = &m_transformationStack.back();
			}

		public:
			virtual ~Renderer2D() { }

			void push(const maths::mat4& matrix, bool override = false)
			{
				if (override)
					m_transformationStack.push_back(matrix);
				else
					m_transformationStack.push_back(m_transformationStack.back() * matrix);

				m_transformationBack = &m_transformationStack.back();
			}

			void pop()
			{
				if (m_transformationStack.size() > 1)
					m_transformationStack.pop_back();

				m_transformationBack = &m_transformationStack.back();
			}			

			virtual void setMask(const Mask* mask) { m_mask = mask; }

			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void drawString( const std::string& text, const maths::vec3& position, const Font font, unsigned int color) { }
			virtual void end() {}
			virtual void flush() = 0;
		};
	}
}
