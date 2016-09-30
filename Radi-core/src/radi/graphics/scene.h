#pragma once

#include <vector>

#include <radi/radi_types.h>
#include <radi/entity/Entity.h>

#include "camera/Camera.h"
#include "light_setup.h"

namespace radi {
	namespace graphics {

		class Renderer3D;

		// TODO: This probably shouldn't be in graphics.
		class RD_API Scene
		{
		private:
			std::vector<entity::Entity*> m_Entities;
			Camera* m_Camera;
			std::vector<LightSetup*> m_LightSetupStack;
		public:
			Scene();
			Scene(Camera* camera);
			~Scene();

			void Add(entity::Entity* entity);
			void PushLightSetup(LightSetup* lightSetup);
			LightSetup* PopLightSetup();
			void SetCamera(Camera* camera);

			void Update();
			void Render(Renderer3D& renderer);

			inline Camera* GetCamera() const { return m_Camera; }
			inline const std::vector<entity::Entity*>& GetEntities() const { return m_Entities; }
		};

	}
}
