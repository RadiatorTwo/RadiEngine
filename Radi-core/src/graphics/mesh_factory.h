#pragma once

#include <radi_types.h>
#include <maths/maths.h>

namespace radi {
	namespace graphics {
		namespace meshfactory {

			//
			// TODO: Eventuell sollte das hier auch mal ein Mesh Objekt zurückgeben.
			//		 Vorerst gibt es nur mal die Daten an die GPU weiter.
			//

			uint CreateQuad(float x, float y, float width, float height);
			uint CreateQuad(const maths::vec2& position, const maths::vec2& size);
		}
	}
}