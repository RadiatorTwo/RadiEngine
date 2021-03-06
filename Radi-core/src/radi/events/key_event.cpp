#include "radi/rd.h"
#include "key_event.h"

namespace radi {
	namespace events {

		KeyEvent::KeyEvent(int keyCode, Event::Type type)
			: Event(type), m_keyCode(keyCode)
		{
		}

		KeyPressedEvent::KeyPressedEvent(int button, int repeat, int modifiers)
			: KeyEvent(button, KeyPressedEvent::GetStaticType()), m_repeat(repeat), m_Modifiers(modifiers)
		{
		}

		KeyReleasedEvent::KeyReleasedEvent(int button)
			: KeyEvent(button, KeyReleasedEvent::GetStaticType())
		{
		}

	}
}