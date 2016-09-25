#include "window.h"
#include "../embedded/Embedded.h"

namespace radi
{
	namespace graphics
	{
				std::map<void*, Window*> Window::s_handles;

		Window::Window(const char *title, int width, int height)
			: m_title(title), m_width(width), m_height(height), m_handle(nullptr), m_closed(false)
		{
			
			if (!init())
			{
				RADI_ERROR("Failed base Window initialization!");
				return;				
			}

			FontManager::add(new Font("SourceSansPro", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, 32));
			audio::SoundManager::init();

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_keys[i] = false;
				m_keyState[i] = false;
				m_keyTyped[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_mouseButtons[i] = false;
				m_mouseState[i] = false;
				m_mouseClicked[i] = false;
			}
		}

		Window::~Window()
		{
			FontManager::clean();
			TextureManager::clean();
    		audio::SoundManager::clean();
		}

		bool Window::init()
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

		bool Window::isKeyPressed(uint keycode) const
		{
			//TODO: Log this!
			if (keycode >= MAX_KEYS)
				return false;
			return m_keys[keycode];
		}


		bool Window::isKeyTyped(uint keycode) const
		{
			//TODO: Log this!
			if (keycode >= MAX_KEYS)
				return false;

			return m_keyTyped[keycode];
		}

		bool Window::isMouseButtonPressed(uint button) const
		{
			//TODO: Log this!
			if (button >= MAX_BUTTONS)
				return false;
			return m_mouseButtons[button];
		}
		
		bool Window::isMouseButtonClicked(uint button) const
		{
			//TODO: Log this!
			if (button >= MAX_BUTTONS)
				return false;
			return m_mouseClicked[button];
		}

		const maths::vec2& Window::getMousePosition() const
		{
			return m_mousePosition;;
		}

		void Window::setVsync(bool enabled)
		{
			// TODO: Not implemented
			m_vsync = enabled;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{
			PlatformUpdate();

			audio::SoundManager::update();
		}

		void Window::updateInput()
		{
			for (int i = 0; i < MAX_KEYS; i++)
				m_keyTyped[i] = m_keys[i] && !m_keyState[i];

			for (int i = 0; i < MAX_BUTTONS; i++)
				m_mouseClicked[i] = m_mouseButtons[i] && !m_mouseState[i];

			memcpy(m_keyState, m_keys, MAX_KEYS);
			memcpy(m_mouseState, m_mouseButtons, MAX_BUTTONS);
		}

		bool Window::closed() const
		{
			return m_closed;
		}

		void Window::RegisterWindowClass(void* handle, Window* window)
		{
			s_handles[handle] = window;
		}

		Window* Window::GetWindowClass(void* handle)
		{
			return s_handles[handle];
		}
	}
}
