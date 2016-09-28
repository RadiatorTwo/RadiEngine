#include "radi/rd.h"
#include "entity.h"

namespace radi {
	namespace entity {

		Entity::Entity()
		{
		}

		void Entity::AddComponent(component::Component* component)
		{
			m_Components.push_back(component);
		}

	}
}