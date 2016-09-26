#include <app/Application.h>

namespace radi {

	Application::Application(const char* name, uint width, uint height)
		: m_name(name), m_width(width), m_height(height)
	{
		s_instance = this;
	}

	Application::~Application()
	{
		delete window;
	}

	void Application::Init()
	{
		window = new graphics::Window(m_name, m_width, m_height);
	}

	void Application::Start()
	{
		Init();
		m_running = true;
		m_suspended = false;
		Run();
	}

	void Application::Suspend()
	{
		m_suspended = true;
	}

	void Application::Resume()
	{
		m_suspended = false;
	}

	void Application::Stop()
	{
		m_running = false;
	}	

	void Application::Run()
	{
		m_Timer = new utils::Timer();
		float timer = 0.0f;
		float updateTimer = 0.0f;
		float updateTick = 1.0f / 60.0f;
		unsigned int frames = 0;
		unsigned int updates = 0;
		while (m_running)
		{
			window->clear();
			if (m_Timer->elapsed() - updateTimer > updateTick)
			{
				window->updateInput();
				OnUpdate();
				updates++;
				updateTimer += updateTick;
			}
			OnRender();
			frames++;
			window->update();
			if (m_Timer->elapsed() - timer > 1.0f)
			{
				timer += 1.0f;
				m_framesPerSecond = frames;
				m_updatesPerSecond = updates;
				frames = 0;
				updates = 0;
				OnTick();
			}
			if (window->closed())
				m_running = false;
		}
	}

}