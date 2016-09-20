#pragma once

#include <GL/glew.h>
#include "../maths/maths.h"
#include <vector>

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
		protected:
			Renderer2D()
			{
				m_transformationStack.push_back(maths::mat4::identity());
				m_transformationBack = &m_transformationStack.back();
			}
		public:
			void push(const maths::mat4& matrix, bool override = false)
			{
				if (override)
					m_transformationStack.push_back(m_transformationStack.back());
				else
					m_transformationStack.push_back(m_transformationStack.back() * matrix);

				m_transformationBack = &m_transformationStack.back();
			}

			void pop()
			{
				if (m_transformationStack.size() > 1)
					m_transformationStack.pop_back();

				m_transformationBack = &m_transformationStack.back();
				//TODO: Add to Log!
			}			

			virtual void begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void drawString(const std::string& text, const maths::vec3& position, unsigned int color) { }
			virtual void end() {}
			virtual void flush() = 0;
		};
	}
}
