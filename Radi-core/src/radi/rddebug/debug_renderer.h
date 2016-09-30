#pragma once

#include "radi/Common.h"
#include "radi/maths/maths.h"
#include "radi/graphics/shaders/Shader.h"
#include "radi/graphics/Mesh.h"
#include "radi/graphics/camera/Camera.h"

namespace radi {
	namespace debug {

		enum class DebugRenderMeshFlags
		{
			NONE = 0,
			WIREFRAME = BIT(0),
			NORMALS = BIT(1),
			BINORMALS = BIT(2),
			TANGENTS = BIT(3)
		};

		class DebugRenderer
		{
		private:
			DebugRenderer() {}
		public:
			RADI_DEBUG_METHOD_V(static void Init())
			RADI_DEBUG_METHOD_V(static void Shutdown())
			RADI_DEBUG_METHOD_V(static void DrawLine(const maths::vec3& start, const maths::vec3& end, uint color = 0xffffffff))
			RADI_DEBUG_METHOD_V(static void DrawMesh(const graphics::Mesh* mesh, DebugRenderMeshFlags flags, const maths::mat4& transform = maths::mat4::Identity()))

			RADI_DEBUG_METHOD_V(static void SetCamera(graphics::Camera* camera))

			RADI_DEBUG_METHOD_V(static void Present())
		private:
			RADI_DEBUG_METHOD_V(static void DrawLineInternal(const maths::vec3& start, const maths::vec3& end, uint color))
		};

	}
}