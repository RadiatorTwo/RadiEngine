#pragma once

#include <vector>

#include <radigl.h>
#include <radi_types.h>

#include <radi/graphics/Window.h>
#include <radi/graphics/layers/layer.h>
#include <radi/utils/Timer.h>

namespace radi {

	class Application
	{
	private:
		static Application* s_instance;
	public:
		graphics::Window* window;
	private:
		bool m_running, m_suspended;
		utils::Timer* m_Timer;
		uint m_updatesPerSecond, m_framesPerSecond;

		const char* m_name;
		uint m_width, m_height;

		std::vector<graphics::Layer*> m_layerStack;
	public:
		Application(const char* name, uint width, uint height);
		virtual ~Application();

		virtual void Init();

		void PushLayer(graphics::Layer* layer);
		graphics::Layer* PopLayer();

		void Start();
		void Suspend();
		void Resume();
		void Stop();

	private:
		void OnTick();
		void OnUpdate();
		void OnRender();
	public:
		const uint GetFPS() const { return m_framesPerSecond; }
		const uint GetUPS() const { return m_updatesPerSecond; }
	private:
		void Run();
	public:
		inline static Application& GetApplication() { return *s_instance; }
	};


}