#include "radi/rd.h"

#include <Windows.h>
#include <Windowsx.h>

#include "radi/utils/log.h"
#include <radi/graphics/Window.h>

#include <GL/glew.h>

EXTERN_C IMAGE_DOS_HEADER __ImageBase;

namespace radi {
	namespace graphics {

		using namespace events;

		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

		static HINSTANCE hInstance;
		static HWND hWnd;
		static HDC hDc;

		static PIXELFORMATDESCRIPTOR get_pixel_format()
		{
			PIXELFORMATDESCRIPTOR result = {};
			result.nSize = sizeof(PIXELFORMATDESCRIPTOR);
			result.nVersion = 1;
			result.dwFlags = PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER;
			result.iPixelType = PFD_TYPE_RGBA;
			result.cColorBits = 32;
			result.cDepthBits = 24;
			result.cStencilBits = 8;
			result.cAuxBuffers = 0;
			result.iLayerType = PFD_MAIN_PLANE;
			return result;
		}

		bool Window::PlatformInit()
		{
			hInstance = (HINSTANCE)&__ImageBase;

			WNDCLASS winClass = {};
			winClass.hInstance = hInstance; // GetModuleHandle(0);
			winClass.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;
			winClass.lpfnWndProc = (WNDPROC)WndProc;
			winClass.lpszClassName = "Radi Win32 Window";
			winClass.hCursor = LoadCursor(NULL, IDC_ARROW);
			winClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);

			if (!RegisterClassA(&winClass))
			{
				// TODO: Handle error
				RADI_ERROR("Could not register Win32 class!");
				return false;
			}

			RECT size = { 0, 0, m_Width, m_Height };
			AdjustWindowRectEx(&size, WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN, false, WS_EX_APPWINDOW | WS_EX_WINDOWEDGE);

			hWnd = CreateWindowExA(WS_EX_APPWINDOW | WS_EX_WINDOWEDGE,
				winClass.lpszClassName, m_Title,
				WS_OVERLAPPEDWINDOW | WS_CLIPSIBLINGS | WS_CLIPCHILDREN,
				GetSystemMetrics(SM_CXSCREEN) / 2 - m_Width / 2,
				GetSystemMetrics(SM_CYSCREEN) / 2 - m_Height / 2,
				// TODO: This requires some... attention
				size.right + (-size.left), size.bottom + (-size.top), NULL, NULL, hInstance, NULL);

			if (!hWnd)
			{
				RADI_ERROR("Could not create window!");
				return false;
			}

			RegisterWindowClass(hWnd, this);

			hDc = GetDC(hWnd);
			PIXELFORMATDESCRIPTOR pfd = get_pixel_format();
			int pixelFormat = ChoosePixelFormat(hDc, &pfd);
			if (pixelFormat)
			{
				if (!SetPixelFormat(hDc, pixelFormat, &pfd))
				{
					RADI_ERROR("Failed setting pixel format!");
					return false;
				}
			}
			else
			{
				RADI_ERROR("Failed choosing pixel format!");
				return false;
			}

			HGLRC hrc = wglCreateContext(hDc);
			if (hrc)
			{
				if (!wglMakeCurrent(hDc, hrc))
				{
					RADI_ERROR("Failed setting OpenGL context!");
					return false;
				}
			}
			else
			{
				RADI_ERROR("Failed creating OpenGL context!");
				return false;
			}

			if (glewInit() != GLEW_OK)
			{
				RADI_FATAL("Could not initialize GLEW!");
				return false;
			}

			ShowWindow(hWnd, SW_SHOW);
			SetFocus(hWnd);
			// resize

			return true;
		}

		void Window::PlatformUpdate()
		{
			MSG message;
			while (PeekMessage(&message, hWnd, NULL, NULL, PM_REMOVE) > 0)
			{
				if (message.message == WM_QUIT)
				{
					m_Closed = true;
					return;
				}
				TranslateMessage(&message);
				DispatchMessage(&message);
			}

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

			SwapBuffers(hDc);
		}

		void Window::SetMousePosition(const maths::vec2& position)
		{
			POINT pt = { (LONG)position.x, (LONG)position.y };
			ClientToScreen(hWnd, &pt);
			SetCursorPos(pt.x, pt.y);
		}

		void Window::SetMouseCursor(int cursor)
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

		void key_callback(Window* window, int flags, int key, uint message)
		{
			bool pressed = message == WM_KEYDOWN || message == WM_SYSKEYDOWN;
			bool* keyState = window->m_KeyState;
			keyState[key] = pressed;

			bool repeat = (flags >> 30) & 1;

			if (pressed)
				window->m_EventCallback(KeyPressedEvent(key, repeat));
			else
				window->m_EventCallback(KeyReleasedEvent(key));
		}

		void mouse_button_callback(Window* window, int button, int x, int y)
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

			window->m_MouseButtons[button] = down;
			window->m_MousePosition.x = (float)x;
			window->m_MousePosition.y = (float)y;

			RADI_ASSERT(window->m_EventCallback);

			if (down)
				window->m_EventCallback(MousePressedEvent(button, (float)x, (float)y));
			else
				window->m_EventCallback(MouseReleasedEvent(button, (float)x, (float)y));
		}

		void resize_callback(Window* window, int width, int height)
		{
			window->m_Width = width;
			window->m_Height = height;
		}

		LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
		{
			LRESULT result = NULL;
			Window* window = Window::GetWindowClass(hWnd);
			if (window == nullptr)
				return DefWindowProc(hWnd, message, wParam, lParam);

			switch (message)
			{
			case WM_ACTIVATE:
			{
				if (!HIWORD(wParam)) // Is minimized
				{
					// active
				}
				else
				{
					// inactive
				}

				return 0;
			}
			case WM_SYSCOMMAND:
			{
				switch (wParam)
				{
				case SC_SCREENSAVE:
				case SC_MONITORPOWER:
					return 0;
				}
				result = DefWindowProc(hWnd, message, wParam, lParam);
			} break;
			case WM_CLOSE:
			case WM_DESTROY:
				PostQuitMessage(0);
				break;
			case WM_KEYDOWN:
			case WM_KEYUP:
			case WM_SYSKEYDOWN:
			case WM_SYSKEYUP:
				key_callback(window, lParam, wParam, message);
				break;
			case WM_LBUTTONDOWN:
			case WM_LBUTTONUP:
			case WM_RBUTTONDOWN:
			case WM_RBUTTONUP:
			case WM_MBUTTONDOWN:
			case WM_MBUTTONUP:
				mouse_button_callback(window, message, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
				break;
			case WM_SIZE:
				resize_callback(window, LOWORD(lParam), HIWORD(lParam));
				break;
			default:
				result = DefWindowProc(hWnd, message, wParam, lParam);
			}
			return result;
		}

	}
}