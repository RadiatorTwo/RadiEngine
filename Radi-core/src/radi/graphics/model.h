#pragma once

#include "radi/rd.h"
#include "radi/Common.h"
#include "radi/radi_types.h"
#include "radi/maths/maths.h"

#include "Mesh.h"

namespace radi {
	namespace graphics {

		class RD_API Model : public IRenderable
		{
		private:
			Mesh* m_Mesh;
		public:
			// This eventually needs to be replaced by a global Asset Server.
			Model(const String& path, MaterialInstance* materialInstance = nullptr);
			~Model();

			void Render(Renderer3D& renderer) override;

			inline Mesh* GetMesh() const { return m_Mesh; }
		private:
			struct VertexSet
			{
				std::vector<maths::vec3> positions, normals;
				std::vector<maths::vec2> uvs;
			};

			// TODO: Replace with uvec3, whenever that begins to exist
			struct IndexSet
			{
				uint position;
				uint uv;
				uint normal;

				bool operator==(const IndexSet& other) const
				{
					return position == other.position && uv == other.uv && normal == other.normal;
				}
			};

			friend struct std::hash<IndexSet>;

			void Load(const String& path);
			void InsertVertex(std::vector<Vertex>& vertices, std::vector<uint>& indices, std::unordered_map<IndexSet, int32>& mapping, VertexSet& inputVertices, IndexSet& indexSet);
		};

	}
}