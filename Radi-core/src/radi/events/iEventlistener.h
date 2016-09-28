#pragma once

#include "event.h"

namespace radi {
	namespace events {

		class RD_API IEventListener
		{
		public:
			virtual bool OnEvent(const Event& event) = 0;
		};

	}
}