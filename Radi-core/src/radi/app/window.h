#pragma once

#include "radi/rd.h"

#include "radi/maths/vec2.h"

#include "radi/audio/sound_manager.h"
#include "radi/events/Events.h"

#include "radi/graphics/font_manager.h"
#include "radi/graphics/texture_manager.h"

#include "radi/app/Input.h"

namespace radi {

	typedef std::function<void(events::Event& event)> WindowEventCallback;

	struct WindowProperties
	{
		String title;
		uint width, height;
		bool fullscreen;
	};

	class RD_API Window
	{
	private:
		static std::map<void*, Window*> s_Handles;
	private:
		WindowProperties m_Properties;
		bool m_Closed;
		void* m_Handle;

		bool m_Vsync;
		WindowEventCallback m_EventCallback;
		InputManager* m_InputManager;
	public:
		Window(const char *name, uint width, uint height, bool fullscreen = false);
		~Window();
		void Clear() const;
		void Update();
		bool Closed() const;

		void SetTitle(const String& title);

		inline uint GetWidth() const { return m_Properties.width; }
		inline uint GetHeight() const { return m_Properties.height; }

		void SetVsync(bool enabled);
		inline bool IsVsync() const { return m_Vsync; }

		inline InputManager* GetInputManager() const { return m_InputManager; }

		void SetEventCallback(const WindowEventCallback& callback);
	private:
		bool Init();

		bool PlatformInit();
		void PlatformUpdate();

		// Window event callbacks (TODO: more platform independent)
		friend void ResizeCallback(Window* window, int32 width, int32 height);
		friend void FocusCallback(Window* window, bool focused);
	public:
		static void RegisterWindowClass(void* handle, Window* window);
		static Window* GetWindowClass(void* handle);
	};

}
