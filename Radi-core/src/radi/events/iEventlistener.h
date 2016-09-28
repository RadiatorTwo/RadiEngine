#pragma once

#include "event.h"

namespace radi {
	namespace events {

		class RD_API IEventListener
		{
		public:
			virtual void OnEvent(Event& event) = 0;
		};

	}
}