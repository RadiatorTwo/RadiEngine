#include "transform_component.h"

namespace radi {
	namespace entity {
		namespace component {

			TransformComponent::TransformComponent(const maths::mat4& transform)
				: transform(transform)
			{
			}

		}
	}
}