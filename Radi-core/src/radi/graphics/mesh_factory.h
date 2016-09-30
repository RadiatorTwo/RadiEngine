#pragma once

#include "radi/Common.h"
#include "radi/radi_types.h"
#include "radi/maths/maths.h"

#include "radi/graphics/Mesh.h"
#include "radi/graphics/Material.h"
#include "radi/graphics/API/VertexArray.h"

namespace radi {
	namespace graphics {
		namespace MeshFactory {

			//
			// TODO: Return a Mesh instead of a VertexArray
			//

			RD_API Mesh* CreateQuad(float x, float y, float width, float height, MaterialInstance* material);
			RD_API Mesh* CreateQuad(const maths::vec2& position, const maths::vec2& size, MaterialInstance* material);

			RD_API Mesh* CreateCube(float size, MaterialInstance* material);
			RD_API Mesh* CreatePlane(float width, float height, const maths::vec3& normal, MaterialInstance* material);

		}
	}
}