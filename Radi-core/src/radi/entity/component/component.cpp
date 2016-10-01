#include "radi/rd.h"
#include "component.h"

namespace radi {
	namespace entity {
		namespace component {

			Component::Component(Entity* entity)
				: m_Entity(entity)
			{
			}

		}
	}
}