#pragma once

#include "buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include "material.h"

#include "iRenderable.h"

namespace radi {
	namespace graphics {

		class Renderer3D;

		struct Vertex
		{
			maths::vec3 position;
			maths::vec3 normal;
			maths::vec2 uv;
		};

		class Mesh : public IRenderable
		{
		private:
			VertexArray* m_vertexArray;
			IndexBuffer* m_indexBuffer;
			MaterialInstance* m_materialInstance;
		public:
			Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, MaterialInstance* materialInstance);
			~Mesh();

			inline void SetMaterial(MaterialInstance* materialInstance) { m_materialInstance = materialInstance; }
			inline MaterialInstance* GetMaterialInstance() const { return m_materialInstance; }

			void Render(Renderer3D& renderer) override;
		};

	}
}