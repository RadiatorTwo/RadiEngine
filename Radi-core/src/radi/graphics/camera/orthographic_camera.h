#pragma once

#include "camera.h"

namespace radi {
	namespace graphics {

		class RD_API OrthographicCamera : public Camera
		{
		private:

		public:
			OrthographicCamera(const maths::mat4& projectionMatrix);
			~OrthographicCamera();
			void Focus() override;
			void Update() override;

		};

	}
}