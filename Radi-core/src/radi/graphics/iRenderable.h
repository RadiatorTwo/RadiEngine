#pragma once

namespace radi {
	namespace graphics {

		class Renderer3D;

		class IRenderable
		{
		public:
			virtual void Render(Renderer3D& renderer) = 0;
		};

	}
}