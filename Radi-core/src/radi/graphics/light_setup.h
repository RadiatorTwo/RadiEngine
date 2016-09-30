#pragma once

#include "Light.h"

namespace radi {
	namespace graphics {

		class RD_API LightSetup
		{
		private:
			std::vector<Light*> m_Lights;
		public:
			LightSetup();
			~LightSetup();

			Light* Add(Light* light);
			void Remove(Light* light);

			inline const std::vector<Light*>& GetLights() const { return m_Lights; }
		};

	}
}