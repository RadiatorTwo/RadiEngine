#pragma once

#include "component.h"

#include "radi/common.h"
#include <radi/graphics/mesh.h>

namespace radi {
	namespace entity {
		namespace component {

			class RD_API MeshComponent : public Component
			{
			public:
				graphics::Mesh* mesh;
			public:
				MeshComponent(graphics::Mesh* mesh);

				static ComponentType* GetStaticType()
				{
					static ComponentType type({ "Mesh" });
					return &type;
				}

				inline virtual ComponentType* GetType() const override { return GetStaticType(); }
			};

		}
	}
}