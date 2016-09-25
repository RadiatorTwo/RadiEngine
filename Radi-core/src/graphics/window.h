#pragma once

#include <iostream>
#include <radigl.h>

#include "../maths/vec2.h"
#include "font_manager.h"
#include "texture_manager.h"
#include "../audio/sound_manager.h"

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
			
			maths::vec2 m_mousePosition;
			bool m_vsync;
		public:
			Window(const char *name, int width, int height);
			~Window();
			void clear() const;
			void update();
			void updateInput();
			bool closed() const;

			inline int getWidth() const { return m_width; }
			inline int getHeight() const { return m_height; }
			
			bool isKeyPressed(uint keycode) const;
			bool isKeyTyped(uint keycode) const;
			bool isMouseButtonPressed(uint button) const;
			bool isMouseButtonClicked(uint button) const;
			const maths::vec2& getMousePosition() const;

			void setVsync(bool enabled);
			bool isVsync() const { return m_vsync; }
		private:
			bool init();
			friend void window_resize(GLFWwindow* window, int width, int height);
			friend void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
			friend void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
			friend void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
		};
	}
}