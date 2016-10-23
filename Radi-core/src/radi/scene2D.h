#pragma once

#include "radi/rd.h"
#include "graphics/camera/orthographic_camera.h"
#include "graphics/renderer2d.h"
#include "entity/entity.h"

namespace radi {

	class RD_API Scene2D
	{
	private:
		graphics::OrthographicCamera* m_Camera;
		graphics::Renderer2D* m_Renderer;

		std::vector<entity::Entity*> m_Entities;
	public:
		Scene2D();
		Scene2D(const maths::mat4& projectionMatrix);
		~Scene2D();

		void Add(entity::Entity* entity);
		void Remove(entity::Entity* entity);
		void Remove(graphics::Sprite* sprite);

		//virtual void OnUpdate();
		virtual void OnUpdate();
		virtual void OnRender(graphics::Renderer2D& renderer);

		void OnRender();

		inline graphics::Renderer2D* GetRenderer() { return m_Renderer; }
		inline graphics::OrthographicCamera* GetCamera() { return m_Camera; }
	};

}