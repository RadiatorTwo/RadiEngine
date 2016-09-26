#pragma once

#include "event.h"

namespace radi {
	namespace events {

		class IEventListener
		{
		public:
			virtual bool OnEvent(const Event& event) = 0;
		};

	}
}