#pragma once

#include "radi/common.h"
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
				MOUSE_MOVED = BIT(4)
			};
		protected:
			bool m_handled;
			Type m_type;
		protected:
			Event(Type type);
		public:			
			inline Type GetType() const { return m_type; }
			inline bool IsHandled() const { return m_handled; }

			virtual String ToString() const;

			static String TypeToString(Type type);
		};

	}
}