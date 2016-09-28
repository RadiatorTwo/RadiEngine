#include "radi/rd.h"
#include "window.h"

#include "radi/utils/log.h"

#include "../embedded/Embedded.h"
#include <GL/glew.h>

namespace radi
{
	namespace graphics
	{
		std::map<void*, Window*> Window::s_Handles;

		Window::Window(const char *title, uint width, uint height)
			: m_Title(title), m_Width(width), m_Height(height), m_Handle(nullptr), m_Closed(false), m_EventCallback(nullptr)
		{
			if (!Init())
			{
				RADI_ERROR("Failed base Window initialization!");
				return;
			}

			FontManager::add(new Font("SourceSansPro", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, 32));

			audio::SoundManager::init();

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_KeyState[i] = false;
				m_LastKeyState[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_MouseButtons[i] = false;
				m_MouseState[i] = false;
				m_MouseClicked[i] = false;
			}
			m_MouseGrabbed = true;
			m_KeyModifiers = 0;
		}

		Window::~Window()
		{
			FontManager::clean();
			TextureManager::clean();
			audio::SoundManager::clean();
		}

		bool Window::Init()
		{
			if (!PlatformInit())
			{
				RADI_FATAL("Failed to initialize platform!");
				return false;
			}

			glEnable(GL_DEPTH_TEST);
			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			RADI_WARN("----------------------------------");
			RADI_WARN(" OpenGL:");
			RADI_WARN("    ", glGetString(GL_VERSION));
			RADI_WARN("    ", glGetString(GL_VENDOR));
			RADI_WARN("    ", glGetString(GL_RENDERER));
			RADI_WARN("----------------------------------");
			return true;
		}

		bool Window::IsKeyPressed(uint keycode) const
		{
			// TODO: Log this!
			if (keycode >= MAX_KEYS)
				return false;

			return m_KeyState[keycode];
		}

		bool Window::IsMouseButtonPressed(uint button) const
		{
			// TODO: Log this!
			if (button >= MAX_BUTTONS)
				return false;

			return m_MouseButtons[button];
		}

		bool Window::IsMouseButtonClicked(uint button) const
		{
			// TODO: Log this!
			if (button >= MAX_BUTTONS)
				return false;

			return m_MouseClicked[button];
		}

		const maths::vec2& Window::GetMousePosition() const
		{
			return m_MousePosition;
		}

		const bool Window::IsMouseGrabbed() const
		{
			return m_MouseGrabbed;
		}

		void Window::SetMouseGrabbed(bool grabbed)
		{
			m_MouseGrabbed = grabbed;
		}

		void Window::SetVsync(bool enabled)
		{
			// TODO: Not implemented
			m_Vsync = enabled;
		}

		void Window::Clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::Update()
		{
			PlatformUpdate();
			audio::SoundManager::update();
		}

		void Window::UpdateInput()
		{
			for (int i = 0; i < MAX_BUTTONS; i++)
				m_MouseClicked[i] = m_MouseButtons[i] && !m_MouseState[i];

			memcpy(m_LastKeyState, m_KeyState, MAX_KEYS);
			memcpy(m_MouseState, m_MouseButtons, MAX_BUTTONS);
		}

		bool Window::Closed() const
		{
			return m_Closed;
		}

		void Window::SetEventCallback(const WindowEventCallback& callback)
		{
			m_EventCallback = callback;
		}

		void Window::RegisterWindowClass(void* handle, Window* window)
		{
			s_Handles[handle] = window;
		}

		Window* Window::GetWindowClass(void* handle)
		{
			if (handle == nullptr)
				return s_Handles.begin()->second;

			return s_Handles[handle];
		}
	}
}
