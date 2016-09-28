#pragma once

#include "event.h"
#include "../maths/vec2.h"

namespace radi {
	namespace events {

		class RD_API MouseButtonEvent : public Event
		{
		protected:
			int m_button;
			maths::vec2 m_position;
		protected:
			MouseButtonEvent(int button, float x, float y, Event::Type type);
		public:
			inline const int GetButton() const { return m_button; }
			inline const float GetX() const { return m_position.x; }
			inline const float GetY() const { return m_position.y; }
			inline const maths::vec2& GetPosition() const { return m_position; }

			inline static int GetStaticType() { return (int)Event::Type::MOUSE_PRESSED | (int)Event::Type::MOUSE_RELEASED; }
		};

		class RD_API MousePressedEvent : public MouseButtonEvent
		{
		public:
			MousePressedEvent(int button, float x, float y);

			String ToString() const override;
			
			inline static Type GetStaticType() { return Event::Type::MOUSE_PRESSED; }
		};

		class RD_API MouseReleasedEvent : public MouseButtonEvent
		{
		public:
			MouseReleasedEvent(int button, float x, float y);

			inline static Type GetStaticType() { return Event::Type::MOUSE_RELEASED; }
		};

		class RD_API MouseMovedEvent : public Event
		{
		private:
			maths::vec2 m_position;
			bool m_dragged;
		public:
			MouseMovedEvent(float x, float y, bool dragged);

			inline const float GetX() const { return m_position.x; }
			inline const float GetY() const { return m_position.y; }
			inline const maths::vec2& GetPosition() const { return m_position; }
			inline const bool IsDragged() const { return m_dragged; }

			inline static Type GetStaticType() { return Event::Type::MOUSE_MOVED; }
		};

	}
}