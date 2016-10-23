#include "radi/rd.h"
#include "Entity.h"

#include "radi/rddebug/debug_menu.h"

namespace radi {
	namespace entity {

		using namespace component;
		using namespace maths;

		// Debug Variables
		static bool s_StaticInitialized = false;

		Entity::Entity()
		{
		}

		Entity::Entity(graphics::Sprite* sprite, const maths::mat4& transform)
			: transform(rdnew TransformComponent(this, transform)), m_BoundingBox(&sprite->GetBoundingBox())
		{
			//AddComponent(new SpriteComponent(sprite));
			//AddComponent(new TransformComponent(transform));
			this->transform->transform = maths::mat4::Translate(sprite->GetPosition());
			AddComponent(rdnew SpriteComponent(this, sprite));
			Init();
		}

		Entity::Entity(graphics::Mesh* mesh, const maths::mat4& transform)
			: transform(rdnew TransformComponent(this, transform)), m_BoundingBox(nullptr) // TODO: Use Mesh's bounding box
		{
			//AddComponent(new MeshComponent(mesh));
			//AddComponent(new TransformComponent(transform));
			AddComponent(rdnew MeshComponent(this, mesh));
			Init();
		}

		void Entity::Init()
		{
			StaticInit();

			AddComponent(this->transform);
		}

		void Entity::StaticInit()
		{
			if (s_StaticInitialized)
				return;

			//debug::DebugMenu::Add("Render Physics", &s_DebugRenderPhysics2DComponent);

			s_StaticInitialized = true;
		}

		void Entity::OnUpdate(const Timestep& ts)
		{
		}

		void Entity::OnRender(graphics::Renderer2D& renderer)
		{			
		}

		void Entity::AddComponent(component::Component* component)
		{
			m_Components.push_back(component);
		}
	}
}