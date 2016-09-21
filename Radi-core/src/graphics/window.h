#pragma once

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "font_manager.h"

namespace radi
{
	namespace graphics
	{
#define MAX_KEYS 1024
#define MAX_BUTTONS 32
		class Window
		{
		private:		
			const char *m_title;
			int m_width, m_height;
			GLFWwindow *m_window;
			bool m_closed;

			bool m_keys[MAX_KEYS];
			bool m_keyState[MAX_KEYS];
			bool m_keyTyped[MAX_KEYS];
			bool m_mouseButtons[MAX_BUTTONS];
			bool m_mouseState[MAX_BUTTONS];
			bool m_mouseClicked[MAX_BUTTONS];
			double mx, my;
		public:
			Window(const char *name, int width, int height);
			~Window();
			void clear() const;
			void update();
			bool closed() const;

			inline int getWidth() const { return m_width; }
			inline int getHeight() const { return m_height; }

			bool isKeyPressed(unsigned int keycode) const;
			bool isKeyTyped(unsigned int keycode) const;
			bool isMouseButtonPressed(unsigned int button) const;
			bool isMouseButtonClicked(unsigned int button) const;
			void getMousePosition(double& x, double& y) const;
		private:
			bool init();
			friend static void window_resize(GLFWwindow* window, int width, int height);
			friend static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend static void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}