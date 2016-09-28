#pragma once

#include <vector>

#include "font.h"
#include "texture.h"
#include "Mask.h"
#include "../maths/maths.h"
#include "postfx/post_effects.h"

namespace radi
{
	namespace graphics
	{
		class Renderable2D;

		enum class RD_API RenderTarget
		{
			SCREEN = 0,
			BUFFER = 1
		};

		class RD_API Renderer2D
		{
		protected:
			std::vector<maths::mat4> m_transformationStack;
			const maths::mat4* m_transformationBack;
			const Mask* m_mask;
			RenderTarget m_target;
			PostEffects* m_postEffects;
			bool m_postEffectsEnabled;
		protected:
			Renderer2D() : m_mask(nullptr), m_postEffectsEnabled(true)
			{
				m_transformationStack.push_back(maths::mat4::Identity());
				m_transformationBack = &m_transformationStack.back();
				m_target = RenderTarget::SCREEN;
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

			inline void SetRenderTarget(RenderTarget target) { m_target = target; }
			inline const RenderTarget GetRenderTarget() const { return m_target; }

			inline void SetPostEffects(bool enabled) { m_postEffectsEnabled = enabled; }
			inline bool GetPostEffects() const { return m_postEffectsEnabled; }
			inline void AddPostEffectsPass(PostEffectsPass* pass) { m_postEffects->Push(pass); }

			virtual void setMask(const Mask* mask) { m_mask = mask; }

			virtual void Begin() {}
			virtual void submit(const Renderable2D* renderable) = 0;
			virtual void drawString(const String& text, const maths::vec3& position, const Font& font, unsigned int color) { }
			virtual void end() {}
			virtual void Present() = 0;
		};
	}
}
