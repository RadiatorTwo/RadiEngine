#include "scene.h"

#include "renderer3D.h"

namespace radi {
	namespace graphics {

		Scene::Scene()
		{

		}

		Scene::~Scene()
		{
			for (uint i = 0; i < m_meshes.size(); i++)
				delete m_meshes[i];

			m_meshes.clear();
		}

		void Scene::Add(Mesh* mesh)
		{
			m_meshes.push_back(mesh);
		}

		void Scene::Render(Renderer3D& renderer)
		{
			for (Mesh* mesh : m_meshes)
				renderer.Submit(mesh);
		}

	}
}