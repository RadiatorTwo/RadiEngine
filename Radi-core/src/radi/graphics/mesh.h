#pragma once

#include "radi/Common.h"
#include "API/VertexArray.h"
#include "API/IndexBuffer.h"
#include "Material.h"

#include "IRenderable.h"

namespace radi {
	namespace graphics {

		class Renderer3D;

		struct RD_API Vertex
		{
			maths::vec3 position;
			maths::vec3 normal;
			maths::vec2 uv;
			maths::vec3 binormal;
			maths::vec3 tangent;
		};

		class RD_API Mesh : public IRenderable
		{
		private:
			API::VertexArray* m_VertexArray;
			API::IndexBuffer* m_IndexBuffer;
			MaterialInstance* m_MaterialInstance;

#ifdef RADI_DEBUG
			Vertex* m_DebugVertexData;
			uint m_DebugVertexDataCount;
			bool m_DebugDraw;
#endif
		public:
			Mesh(API::VertexArray* vertexArray, API::IndexBuffer* indexBuffer, MaterialInstance* materialInstance);
			Mesh(const Mesh* mesh);
			~Mesh();

			inline void SetMaterial(MaterialInstance* materialInstance) { m_MaterialInstance = materialInstance; }
			inline MaterialInstance* GetMaterialInstance() const { return m_MaterialInstance; }

			void Render(Renderer3D& renderer) override;

#ifdef RADI_DEBUG
			void DebugRender(const maths::mat4& transform);

			inline void SetDebugData(Vertex* vertices, uint count) { m_DebugVertexData = vertices; m_DebugVertexDataCount = count; }
			inline uint GetDebugData(Vertex*& vertices) const { vertices = m_DebugVertexData; return m_DebugVertexDataCount; }

			inline void SetDebugDraw(bool debug) { m_DebugDraw = debug; }
#endif
		};

	}
}
