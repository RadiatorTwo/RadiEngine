#pragma once

#include "radi/common.h"
#include <radi/radi_types.h>
#include <radi/maths/maths.h>

#include <radi/graphics/mesh.h>
#include <radi/graphics/material.h>
#include <radi/graphics/buffers/vertexarray.h>

namespace radi {
	namespace graphics {
		namespace meshfactory {

			// TODO: Return a Mesh instead of a VertexArray

			RD_API VertexArray* CreateQuad(float x, float y, float width, float height);
			RD_API VertexArray* CreateQuad(const maths::vec2& position, const maths::vec2& size);

			RD_API Mesh* CreateCube(float size, MaterialInstance* material);
		}
	}
}