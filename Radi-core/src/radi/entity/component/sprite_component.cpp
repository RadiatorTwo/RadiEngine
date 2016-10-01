#include "radi/rd.h"
#include "sprite_component.h"

namespace radi {
	namespace entity {
		namespace component {

			SpriteComponent::SpriteComponent(graphics::Sprite* sprite)
				: sprite(sprite)
			{
			}

		}
	}
}