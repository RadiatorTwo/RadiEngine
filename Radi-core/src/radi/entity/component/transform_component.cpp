#include "radi/rd.h"
#include "transform_component.h"

namespace radi {
	namespace entity {
		namespace component {

			TransformComponent::TransformComponent(Entity* entity, const maths::mat4& transform)
				: Component(entity), transform(transform)
			{
			}

		}
	}
}