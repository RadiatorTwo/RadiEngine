#include "radi/rd.h"
#include "window_event.h"

namespace radi { namespace events {

	ResizeWindowEvent::ResizeWindowEvent(uint width, uint height)
		: Event(ResizeWindowEvent::GetStaticType()), m_Size(maths::tvec2<uint>(width, height))
	{
	}

} }