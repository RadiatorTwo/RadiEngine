#include "window.h"
#include "../embedded/Embedded.h"

namespace radi
{
	namespace graphics
	{
		void window_resize(GLFWwindow* window, int width, int height);
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);

		Window::Window(const char *title, int width, int height)
		{
			m_title = title;
			m_width = width;
			m_height = height;
			if (!init())
				glfwTerminate();

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
			audio::SoundManager::clean();
			FontManager::clean();
			TextureManager::clean();
			glfwTerminate();
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				RADI_FATAL("Failed to initialize GLFW!");
				return false;
			}

			m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
			if (!m_window)
			{
				glfwTerminate();
				RADI_FATAL("Failed to create GLFW window!");
				return false;
			}

			glfwMakeContextCurrent(m_window);
			glfwSetWindowUserPointer(m_window, this);
			glfwSetFramebufferSizeCallback(m_window, window_resize);
			glfwSetKeyCallback(m_window, key_callback);
			glfwSetMouseButtonCallback(m_window, mouse_button_callback);
			glfwSetCursorPosCallback(m_window, cursor_position_callback);
			glfwSwapInterval(0.0);

			if (glewInit() != GLEW_OK)
			{
				RADI_FATAL("Could not initialize GLEW!");
				return false;
			}

			glEnable(GL_BLEND);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

			RADI_WARN("OpenGL ", glGetString(GL_VERSION));

			return true;
		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			//TODO: Log this!
			if (keycode >= MAX_KEYS)
				return false;
			return m_keys[keycode];
		}


		bool Window::isKeyTyped(unsigned int keycode) const
		{
			//TODO: Log this!
			if (keycode >= MAX_KEYS)
				return false;

			return m_keyTyped[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			//TODO: Log this!
			if (button >= MAX_BUTTONS)
				return false;
			return m_mouseButtons[button];
		}
		
		bool Window::isMouseButtonClicked(unsigned int button) const
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

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{			
			// TODO: Gescheites OpenGL error checking!
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;

			glfwPollEvents();
			glfwSwapBuffers(m_window);

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
			return glfwWindowShouldClose(m_window) == 1;
		}

		void window_resize(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->m_width = width;
			win->m_height = height;
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->m_keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->m_mouseButtons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->m_mousePosition.x = (float)xpos;
			win->m_mousePosition.y = (float)ypos;
		}
	}
}
