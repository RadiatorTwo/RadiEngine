#include "radi/rd.h"
#include "Entity.h"

#include "radi/rddebug/debug_menu.h"

namespace radi {
	namespace entity {

		using namespace component;
		using namespace maths;

		// Debug Variables
		static bool s_StaticInitialized = false;
		static bool s_DebugRenderPhysics2DComponent = false;

		Entity::Entity()
		{
		}

		Entity::Entity(graphics::Sprite* sprite, const maths::mat4& transform)
			: transform(rdnew TransformComponent(this, transform)), m_BoundingBox(&sprite->GetBoundingBox())
		{
			this->transform->transform = maths::mat4::Translate(sprite->GetPosition());
			AddComponent(rdnew SpriteComponent(this, sprite));
			Init();
		}

		Entity::Entity(graphics::Mesh* mesh, const maths::mat4& transform)
		{
			AddComponent(rdnew MeshComponent(this, mesh));
			if (this->transform)
				Init();
			else
				AddComponent(rdnew TransformComponent(this, transform));
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

			radi::debug::DebugMenu::Add("Render Physics", &s_DebugRenderPhysics2DComponent);

			s_StaticInitialized = true;
		}

		void Entity::AddComponent(component::Component* component)
		{
			if (component->GetType() == Physics2DComponent::GetStaticType())
				((Physics2DComponent*)component)->SetPosition(transform->transform.GetPosition());
			m_Components.push_back(component);
		}

		void Entity::OnUpdate(const Timestep& ts)
		{
			Physics2DComponent* p = GetComponent<Physics2DComponent>();
			if (p)
			{
				SpriteComponent* s = GetComponent<SpriteComponent>();
				const vec2& pos = p->GetPosition();
				const vec2& size = s->sprite->GetSize();
				transform->transform.SetPosition(pos);
			}
		}

		void Entity::OnRender(graphics::Renderer2D& renderer)
		{
			if (s_DebugRenderPhysics2DComponent)
			{
				Physics2DComponent* p = GetComponent<Physics2DComponent>();
				if (p)
					p->DebugRender(renderer);
			}
		}
	}
}