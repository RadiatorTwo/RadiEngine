#include "radi/rd.h"
#include "mesh_component.h"

namespace radi {
	namespace entity {
		namespace component {

			MeshComponent::MeshComponent(Entity* entity, graphics::Mesh* mesh)
				: Component(entity), mesh(mesh)
			{
			}

		}
	}
}