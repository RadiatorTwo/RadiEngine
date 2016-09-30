#include "radi/rd.h"
#include "Window.h"

#include "radi/graphics/Renderer.h"

#include "radi/utils/Log.h"

#include "radi/embedded/Embedded.h"
#include <FreeImage.h>

namespace radi {

	using namespace graphics;

	std::map<void*, Window*> Window::s_Handles;

	Window::Window(const char *title, uint width, uint height, bool fullscreen)
		: m_Properties({ String(title), width, height, fullscreen }), m_Handle(nullptr), m_Closed(false), m_EventCallback(nullptr)
	{
		if (!Init())
		{
			RADI_ERROR("Failed base Window initialization!");
			return;
		}

		FontManager::SetScale(maths::vec2(m_Properties.width / 32.0f, m_Properties.height / 18.0f)); // TODO: Seriously
		FontManager::Add(new Font("SourceSansPro", internal::DEFAULT_FONT, internal::DEFAULT_FONT_SIZE, 32));

		FreeImage_Initialise();

		audio::SoundManager::Init();
		m_InputManager = new InputManager();
	}

	Window::~Window()
	{
		FontManager::Clean();
		TextureManager::Clean();
		audio::SoundManager::Clean();
	}

	bool Window::Init()
	{
		if (!PlatformInit())
		{
			RADI_FATAL("Failed to initialize platform!");
			return false;
		}

		Renderer::Init();

		SetTitle(m_Properties.title);
		return true;
	}

	void Window::SetVsync(bool enabled)
	{
		// TODO: Not implemented
		m_Vsync = enabled;
	}

	void Window::Clear() const
	{
		Renderer::Clear(RENDERER_BUFFER_COLOR | RENDERER_BUFFER_DEPTH);
	}

	void Window::Update()
	{
		PlatformUpdate();
		audio::SoundManager::Update();
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