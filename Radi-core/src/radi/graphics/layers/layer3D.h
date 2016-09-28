#pragma once

#include "layer.h"
#include "../scene.h"

namespace radi {
	namespace graphics {

		class Layer3D : public Layer
		{
		protected:
			Scene* m_scene;
			Renderer3D* m_renderer;
		public:
			Layer3D(Scene* scene);
			~Layer3D();

			virtual void Init();
			virtual void OnInit(Renderer3D& renderer, Scene& scene);

			inline Scene* GetScene() const { return m_scene; }

			void OnRender() override;
			virtual void OnRender(Renderer3D& renderer);
		};

	}
}