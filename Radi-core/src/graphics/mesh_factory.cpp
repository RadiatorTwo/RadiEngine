#include "mesh_factory.h"

#include <graphics/batchrenderer2d.h>

#include <radigl.h>
#include <graphics/renderable2d.h>
#include <graphics/shaders/Shader.h>

#define RADI_VERTEX_ARRAYS 1

namespace radi {
	namespace graphics {
		namespace meshfactory {

			VertexArray* CreateQuad(float x, float y, float width, float height)
			{
				using namespace maths;

				VertexData data[4];

				data[0].vertex = vec3(x, y, 0);
				data[0].uv = vec2(0, 1);

				data[1].vertex = vec3(x, y + height, 0);
				data[1].uv = vec2(0, 0);

				data[2].vertex = vec3(x + width, y + height, 0);
				data[2].uv = vec2(1, 0);

				data[3].vertex = vec3(x + width, y, 0);
				data[3].uv = vec2(1, 1);

#if RADI_VERTEX_ARRAYS
				API::Buffer* buffer = new API::Buffer(GL_ARRAY_BUFFER, GL_STATIC_DRAW);
				buffer->Bind();
				buffer->SetData(RENDERER_VERTEX_SIZE * 4, data);

				buffer->layout.Push<vec3>("position");
				buffer->layout.Push<vec2>("uv");
				buffer->layout.Push<vec2>("mask_uv");
				buffer->layout.Push<float>("tid");
				buffer->layout.Push<float>("mid");
				buffer->layout.Push<byte>("color", 4, true);

				VertexArray* result = new VertexArray();
				result->bind();
				result->PushBuffer(buffer);
#else
#error non-vertex arrays noch nicht drin
#endif
				return result;
			}

			VertexArray* CreateQuad(const maths::vec2& position, const maths::vec2& size)
			{
				return CreateQuad(position.x, position.y, size.x, size.y);
			}

			}
		}
	}