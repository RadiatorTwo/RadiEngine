#pragma once

#include "radi/common.h"
#include "renderer3D.h"

namespace radi {
	namespace graphics {

		class RD_API ForwardRenderer : public Renderer3D
		{
		public:
			ForwardRenderer();
			void Init() override;
			void Begin() override;
			void Submit(const RenderCommand& command) override;
			void SubmitMesh(Camera* camera, Mesh* mesh, const maths::mat4& transform) override;
			void End() override;
			void Present() override;
		private:
			void SetRequiredUniforms(Shader* shader, const std::vector<RendererUniform>& uniforms);
		};

	}
}