#pragma once

#include "radi/Common.h"
#include "radi/radi_string.h"

namespace radi {
	namespace events {

#undef MOUSE_PRESSED
#undef MOUSE_RELEASED
#undef MOUSE_MOVED
#undef KEY_PRESSED
#undef KEY_RELEASED

		class RD_API Event
		{
		private:
			friend class EventDispatcher;
		public:
			enum class Type
			{
				KEY_PRESSED = BIT(0),
				KEY_RELEASED = BIT(1),

				MOUSE_PRESSED = BIT(2),
				MOUSE_RELEASED = BIT(3),
				MOUSE_MOVED = BIT(4),

				WINDOW_RESIZE = BIT(5)
			};
		protected:
			bool m_Handled;
			Type m_Type;
		protected:
			Event(Type type);
		public:
			inline Type GetType() const { return m_Type; }
			inline bool IsHandled() const { return m_Handled; }

			virtual String ToString() const;

			static String TypeToString(Type type);
		};

	}
}