#pragma once

#include "../Renderable2D.h"
#include "radi/Common.h"

namespace radi {
	namespace graphics {

		class RD_API Group : public Renderable2D
		{
		private:
			std::vector<Renderable2D*> m_Renderables;
			maths::mat4 m_TransformationMatrix;
		public:
			Group(const maths::mat4& transform);
			~Group();
			void Add(Renderable2D* renderable);
			void Submit(Renderer2D* renderer) const override;

			maths::mat4& GetTransformRef() { return m_TransformationMatrix; }
		};

	}
}