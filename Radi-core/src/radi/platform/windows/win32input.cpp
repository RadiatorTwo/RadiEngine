#include "radi/rd.h"
#include "radi/app/Input.h"
#include "radi/utils/Log.h"

#include <Windows.h>
#include <Windowsx.h>

#include "radi/app/Window.h"
#include "radi/events/Events.h"

namespace radi {

	using namespace events;

	extern HWND hWnd;

	void InputManager::PlatformUpdate()
	{
		// Mouse Events
		POINT mouse;
		GetCursorPos(&mouse);
		ScreenToClient(hWnd, &mouse);

		maths::vec2 mousePos = maths::vec2((float)mouse.x, (float)mouse.y);
		if (mousePos != m_MousePosition)
		{
			m_EventCallback(MouseMovedEvent(mousePos.x, mousePos.y, m_MouseButtons[RD_MOUSE_LEFT]));
			m_MousePosition = mousePos;
		}
	}

	void InputManager::SetMousePosition(const maths::vec2& position)
	{
		POINT pt = { (LONG)position.x, (LONG)position.y };
		ClientToScreen(hWnd, &pt);
		SetCursorPos(pt.x, pt.y);
	}

	void InputManager::SetMouseCursor(int cursor)
	{
		if (cursor == RD_NO_CURSOR)
		{
			SetCursor(RD_NO_CURSOR);
			while (ShowCursor(false) >= 0);
		}
		else
		{
			SetCursor(LoadCursor(NULL, IDC_ARROW));
			ShowCursor(true);
		}
	}

	void KeyCallback(InputManager* inputManager, int flags, int key, uint message)
	{
		bool pressed = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
		inputManager->m_KeyState[key] = pressed;

		bool repeat = (flags >> 30) & 1;

		int modifier = 0;
		switch (key)
		{
		case RD_KEY_CONTROL:
			modifier = RD_MODIFIER_LEFT_CONTROL;
			break;
		case RD_KEY_ALT:
			modifier = RD_MODIFIER_LEFT_ALT;
			break;
		case RD_KEY_SHIFT:
			modifier = RD_MODIFIER_LEFT_SHIFT;
			break;
		}
		if (pressed)
			inputManager->m_KeyModifiers |= modifier;
		else
			inputManager->m_KeyModifiers &= ~(modifier);

		if (pressed)
			inputManager->m_EventCallback(KeyPressedEvent(key, repeat, inputManager->m_KeyModifiers));
		else
			inputManager->m_EventCallback(KeyReleasedEvent(key));
	}

	void MouseButtonCallback(InputManager* inputManager, int button, int x, int y)
	{
		bool down = false;
		switch (button)
		{
		case WM_LBUTTONDOWN:
			button = RD_MOUSE_LEFT;
			down = true;
			break;
		case WM_LBUTTONUP:
			button = RD_MOUSE_LEFT;
			down = false;
			break;
		case WM_RBUTTONDOWN:
			button = RD_MOUSE_RIGHT;
			down = true;
			break;
		case WM_RBUTTONUP:
			button = RD_MOUSE_RIGHT;
			down = false;
			break;
		case WM_MBUTTONDOWN:
			button = RD_MOUSE_MIDDLE;
			down = true;
			break;
		case WM_MBUTTONUP:
			button = RD_MOUSE_MIDDLE;
			down = false;
			break;
		}

		inputManager->m_MouseButtons[button] = down;
		inputManager->m_MousePosition.x = (float)x;
		inputManager->m_MousePosition.y = (float)y;

		RADI_ASSERT(inputManager->m_EventCallback);

		if (down)
			inputManager->m_EventCallback(MousePressedEvent(button, (float)x, (float)y));
		else
			inputManager->m_EventCallback(MouseReleasedEvent(button, (float)x, (float)y));
	}


}