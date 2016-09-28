#pragma once

#include "component.h"

#include "radi/common.h"
#include <radi/maths/maths.h>

namespace radi {
	namespace entity {
		namespace component {

			class RD_API TransformComponent : public Component
			{
			public:
				maths::mat4 transform;
			public:
				TransformComponent(const maths::mat4& transform);

				static ComponentType* GetStaticType()
				{
					static ComponentType type({ "Transform" });
					return &type;
				}

				inline virtual ComponentType* GetType() const override { return GetStaticType(); }
			};

		}
	}
}