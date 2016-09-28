#pragma once

#include <vector>

#include <radi_types.h>
#include <entity/entity.h>

#include "camera/camera.h"

namespace radi {
	namespace graphics {

		class Renderer3D;

		// TODO: This probably shouldn't be in graphics.
		class Scene
		{
		private:
			std::vector<entity::Entity*> m_Entities;
			Camera* m_Camera;
		public:
			Scene();
			Scene(Camera* camera);
			~Scene();
			void Add(entity::Entity* entity);
			void Update();
			void Render(Renderer3D& renderer);

			const std::vector<entity::Entity*>& GetEntities() const { return m_Entities; }
		};

	}
}