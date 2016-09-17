#include "window.h"

namespace radi
{
	namespace graphics
	{
		void resize_window(GLFWwindow* window, int width, int height);

		Window::Window(const char *title, int width, int height)
		{
			m_title = title;
			m_width = width;
			m_height = height;
			if (!init())
				glfwTerminate();

			for (int i = 0; i < MAX_KEYS; i++)
			{
				m_keys[i] = false;
			}

			for (int i = 0; i < MAX_BUTTONS; i++)
			{
				m_buttons[i] = false;
			}
		}

		Window::~Window()
		{
			glfwTerminate();
		}

		bool Window::init()
		{
			if (!glfwInit())
			{
				std::cout << "Failed to initialize GFLW!" << std::endl;
				return false;
			}

			m_window = glfwCreateWindow(m_width, m_height, m_title, NULL, NULL);
			if (!m_window)
			{
				glfwTerminate();
				std::cout << "Failed to create GLFW Window!" << std::endl;
				return false;
			}

			glfwMakeContextCurrent(m_window);
			glfwSetWindowUserPointer(m_window, this);
			glfwSetWindowSizeCallback(m_window, resize_window);
			glfwSetKeyCallback(m_window, key_callback);
			glfwSetMouseButtonCallback(m_window, mouse_button_callback);
			glfwSetCursorPosCallback(m_window, cursor_position_callback);
			glfwSwapInterval(0.0);

			if (glewInit() != GLEW_OK)
			{
				std::cout << "Failed to initialize GLEW!" << std::endl;
				return false;
			}

			//printf("OpenGL %s, GLSL %s\n", glGetString(GL_VERSION), glGetString(GL_SHADING_LANGUAGE_VERSION));
			std::cout << "OpenGL " << glGetString(GL_VERSION) << std::endl;

			return true;
		}

		bool Window::isKeyPressed(unsigned int keycode) const
		{
			//TODO: Log this!
			if (keycode >= MAX_KEYS)
				return false;
			return m_keys[keycode];
		}

		bool Window::isMouseButtonPressed(unsigned int button) const
		{
			//TODO: Log this!
			if (button >= MAX_BUTTONS)
				return false;
			return m_buttons[button];
		}

		void Window::getMousePosition(double& x, double& y) const
		{
			x = mx;
			y = my;
		}

		void Window::clear() const
		{
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		}

		void Window::update()
		{
			GLenum error = glGetError();
			if (error != GL_NO_ERROR)
				std::cout << "OpenGL Error: " << error << std::endl;
			glfwPollEvents();
			glfwSwapBuffers(m_window);
		}

		bool Window::closed() const
		{
			return glfwWindowShouldClose(m_window) == 1;
		}

		void resize_window(GLFWwindow* window, int width, int height)
		{
			glViewport(0, 0, width, height);
		}

		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->m_keys[key] = action != GLFW_RELEASE;
		}

		void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->m_buttons[button] = action != GLFW_RELEASE;
		}

		void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
		{
			Window* win = (Window*)glfwGetWindowUserPointer(window);

			win->mx = xpos;
			win->my = ypos;
		}
	}
}
