#pragma once

#include "event.h"

namespace radi {
	namespace events {

		class RD_API KeyEvent : public Event
		{
		private:
			int m_keyCode;
		public:
			KeyEvent(int keyCode, Event::Type type);

			inline const int GetKeyCode() const { return m_keyCode; }
		};

		class RD_API KeyPressedEvent : public KeyEvent
		{
		private:
			int m_repeat;
		public:
			KeyPressedEvent(int button, int repeat);

			inline const int GetRepeat() const { return m_repeat; }
		};

		class RD_API KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(int button);
		};

	}
}