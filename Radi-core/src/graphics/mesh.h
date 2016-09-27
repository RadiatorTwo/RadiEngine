#pragma once

#include "buffers/VertexArray.h"
#include "buffers/IndexBuffer.h"
#include "material.h"

namespace radi {
	namespace graphics {

		class Renderer3D;

		struct Vertex
		{
			maths::vec3 position;
			maths::vec3 normal;
			maths::vec2 uv;
		};

		class Mesh
		{
		private:
			VertexArray* m_VertexArray;
			IndexBuffer* m_IndexBuffer;
			MaterialInstance* m_MaterialInstance;
		public:
			Mesh(VertexArray* vertexArray, IndexBuffer* indexBuffer, MaterialInstance* materialInstance);
			~Mesh();

			inline MaterialInstance* GetMaterialInstance() const { return m_MaterialInstance; }

			void Render(Renderer3D& renderer);
		};

	}
}