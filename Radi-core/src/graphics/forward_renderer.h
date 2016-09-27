#pragma once

#include "renderer3D.h"

namespace radi {
	namespace graphics {

		class ForwardRenderer : public Renderer3D
		{
		private:

		public:
			ForwardRenderer();
			void Init() override;
			void Begin() override;
			void Submit(Mesh* mesh) override;
			void End() override;
			void Present() override;
		};

	}
}