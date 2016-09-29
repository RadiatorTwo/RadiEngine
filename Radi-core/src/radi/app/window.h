#pragma once

#include "radi/rd.h"

#include "radi/maths/vec2.h"

#include "../audio/sound_manager.h"
#include "radi/events/Events.h"

#include "radi/graphics/font_manager.h"
#include "radi/graphics/texture_manager.h"

#include "radi/app/Input.h"

namespace radi
{
	typedef std::function<void(events::Event& event)> WindowEventCallback;

	class RD_API Window
	{
	private:
		static std::map<void*, Window*> s_Handles;
	private:
		const char *m_Title;
		int m_Width, m_Height;
		bool m_Closed;
		void* m_Handle;

		bool m_Vsync;
		WindowEventCallback m_EventCallback;
		InputManager* m_InputManager;
	public:
		Window(const char *name, uint width, uint height);
		~Window();
		void Clear() const;
		void Update();
		bool Closed() const;

		inline uint GetWidth() const { return m_Width; }
		inline uint GetHeight() const { return m_Height; }

		void SetVsync(bool enabled);
		inline bool IsVsync() const { return m_Vsync; }

		inline InputManager* GetInputManager() const { return m_InputManager; }

		void SetEventCallback(const WindowEventCallback& callback);
	private:
		bool Init();

		bool PlatformInit();
		void PlatformUpdate();

		// Window event callbacks (TODO: more platform independent)
		friend void ResizeCallback(Window* window, int width, int height);
		friend void FocusCallback(Window* window, bool focused);
	public:
		static void RegisterWindowClass(void* handle, Window* window);
		static Window* GetWindowClass(void* handle);
	};

}
