#pragma once

#include <radi_types.h>
#include <maths/maths.h>

#include <graphics/mesh.h>
#include <graphics/material.h>
#include <graphics/buffers/vertexarray.h>

namespace radi {
	namespace graphics {
		namespace meshfactory {

			// TODO: Return a Mesh instead of a VertexArray

			VertexArray* CreateQuad(float x, float y, float width, float height);
			VertexArray* CreateQuad(const maths::vec2& position, const maths::vec2& size);

			Mesh* CreateCube(float size, MaterialInstance* material);
		}
	}
}