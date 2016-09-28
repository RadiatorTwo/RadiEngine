#pragma once

namespace radi {
	namespace events {

		class Event
		{
		public:
			enum class Type
			{
				MOUSE_PRESSED, MOUSE_RELEASED, MOUSE_MOVED,
				KEY_PRESSED, KEY_RELEASED
			};
		protected:
			bool m_handled;
			Type m_type;
		protected:
			Event(Type type);
			inline Type GetType() const { return m_type; }
		};

	}
}