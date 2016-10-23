#include "radi/rd.h"
#include "sprite_component.h"

namespace radi {
	namespace entity {
		namespace component {

			SpriteComponent::SpriteComponent(Entity* entity, graphics::Sprite* sprite)
				: Component(entity), sprite(sprite)
			{
			}

		}
	}
}