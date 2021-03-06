#include "radi/rd.h"
#include "Group.h"

#include "radi/graphics/renderer2d.h"

namespace radi {
	namespace graphics {

		Group::Group(const maths::mat4& transform)
			: m_TransformationMatrix(transform)
		{
		}

		Group::~Group()
		{
			for (uint i = 0; i < m_Renderables.size(); i++)
				rddel m_Renderables[i];
		}

		void Group::Add(Renderable2D* renderable)
		{
			m_Renderables.push_back(renderable);
		}

		void Group::Submit(Renderer2D* renderer) const
		{
			renderer->Push(m_TransformationMatrix);

			for (const Renderable2D* renderable : m_Renderables)
				renderable->Submit(renderer);

			renderer->Pop();
		}

	}
}