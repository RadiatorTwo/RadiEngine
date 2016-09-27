#pragma once

#include <vector>

#include <radi_types.h>
#include "mesh.h"

namespace radi {
	namespace graphics {

		class Renderer3D;

		// TODO: This probably shouldn't be in graphics.
		class Scene
		{
		private:
			std::vector<Mesh*> m_meshes; // TODO: Replace with component-based Entities!
		public:
			Scene();
			~Scene();
			void Add(Mesh* mesh);
			void Render(Renderer3D& renderer);

			const std::vector<Mesh*>& GetMeshes() const { return m_meshes; }
		};

	}
}