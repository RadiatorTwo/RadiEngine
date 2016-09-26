#include "event.h"

namespace radi {
	namespace events {

		Event::Event(Type type)
			: m_type(type), m_handled(false)
		{
		}


	}
}