#include "mesh.h"

#include "renderer3D.h"

namespace radi {
	namespace graphics {

		Mesh::Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, MaterialInstance* materialInstance)
			: m_VertexArray(vertexArray), m_IndexBuffer(indexBuffer), m_MaterialInstance(materialInstance)
		{

		}

		Mesh::~Mesh()
		{
			delete m_VertexArray;
			delete m_IndexBuffer;
			delete m_MaterialInstance;
		}

		void Mesh::Render(Renderer3D& renderer)
		{
			m_MaterialInstance->GetMaterial()->Bind();

			m_VertexArray->bind();
			m_IndexBuffer->bind();
			m_VertexArray->Draw(m_IndexBuffer->GetCount());
			m_IndexBuffer->unbind();
			m_VertexArray->unbind();

			m_MaterialInstance->GetMaterial()->Unbind();
		}

	}
}