#include "radi/rd.h"
#include "Entity.h"

namespace radi {
	namespace entity {

		using namespace component;

		Entity::Entity()
		{
		}

		Entity::Entity(graphics::Sprite* sprite, const maths::mat4& transform)
		{
			AddComponent(new SpriteComponent(sprite));
			AddComponent(new TransformComponent(transform));
		}

		Entity::Entity(graphics::Mesh* mesh, const maths::mat4& transform)
		{
			AddComponent(new MeshComponent(mesh));
			AddComponent(new TransformComponent(transform));
		}

		void Entity::AddComponent(component::Component* component)
		{
			m_Components.push_back(component);
		}		
	}
}