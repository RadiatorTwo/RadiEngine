#include "radi/rd.h"
#include "mesh.h"

#include "renderer3D.h"

namespace radi {
	namespace graphics {

		Mesh::Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, MaterialInstance* materialInstance)
			: m_vertexArray(vertexArray), m_indexBuffer(indexBuffer), m_materialInstance(materialInstance)
		{

		}

		Mesh::~Mesh()
		{
			delete m_vertexArray;
			delete m_indexBuffer;
			delete m_materialInstance;
		}

		void Mesh::Render(Renderer3D& renderer)
		{
			m_materialInstance->Bind();

			m_vertexArray->Bind();
			m_indexBuffer->Bind();
			m_vertexArray->Draw(m_indexBuffer->GetCount());
			m_indexBuffer->Unbind();
			m_vertexArray->Unbind();

			m_materialInstance->Unbind();
		}

	}
}