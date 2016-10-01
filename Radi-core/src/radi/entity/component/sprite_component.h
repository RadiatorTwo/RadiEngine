#pragma once

#include "Component.h"

#include "radi/common.h"
#include "radi/graphics/Sprite.h"

namespace radi {
	namespace entity {
		namespace component {

			class RD_API SpriteComponent : public Component
			{
			public:
				graphics::Sprite* sprite;
			public:
				SpriteComponent(Entity* entity, graphics::Sprite* sprite);

				static ComponentType* GetStaticType()
				{
					static ComponentType type({ "Sprite" });
					return &type;
				}

				inline virtual ComponentType* GetType() const override { return GetStaticType(); }
			};

		}
	}
}
