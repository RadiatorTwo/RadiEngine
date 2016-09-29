#include "radi/rd.h"
#include "window.h"

#include "radi/utils/log.h"

#include "radi/embedded/Embedded.h"
#include <GL/glew.h>

namespace radi
{
	using namespace graphics;

	std::map<void*, Window*> Window::s_Handles;

	Window::Window(const char *title, uint width, uint height)
		: m_Title(title), m_Width(width), m_Height(height), m_Handle(nullptr), m_Closed(false), m_EventCallback(nullptr)
	{
		if (!Init())
		{
			RADI_ERROR("Failed base Window initialization!");
			return;
		}

		FontManager::SetScale(maths::vec2(m_Width / 32.0f, m_Height / 18.0f));
		FontManager::add(new Font("SourceSansPro", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, 32));

		audio::SoundManager::init();
		m_InputManager = new InputManager();
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

	bool Window::Closed() const
	{
		return m_Closed;
	}

	void Window::SetEventCallback(const WindowEventCallback& callback)
	{
		m_EventCallback = callback;
		m_InputManager->SetEventCallback(m_EventCallback);
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
