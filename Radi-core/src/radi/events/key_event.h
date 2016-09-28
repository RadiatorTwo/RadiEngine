#pragma once

#include "event.h"

namespace radi {
	namespace events {

		class RD_API KeyEvent : public Event
		{
		protected:
			int m_keyCode;
			int m_Count;

		public:
			KeyEvent(int keyCode, Event::Type type);

			inline int GetKeyCode() const { return m_keyCode; }

			inline static int GetStaticType() { return (int)Event::Type::KEY_PRESSED | (int)Event::Type::KEY_RELEASED; }
		};

		class RD_API KeyPressedEvent : public KeyEvent
		{
		private:
			int m_repeat;
		public:
			KeyPressedEvent(int button, int repeat);

			inline int GetRepeat() const { return m_repeat; }

			inline static Type GetStaticType() { return Event::Type::KEY_PRESSED; }
		};

		class RD_API KeyReleasedEvent : public KeyEvent
		{
		public:
			KeyReleasedEvent(int button);

			inline static Type GetStaticType() { return Event::Type::KEY_RELEASED; }
		};

	}
}