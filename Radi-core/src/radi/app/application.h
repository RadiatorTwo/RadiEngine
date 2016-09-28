#pragma once

#include "radi/rd.h"
#include "radi/common.h"
#include "radi/radi_types.h"

#include <radi/graphics/window.h>
#include <radi/graphics/layers/layer.h>
#include <radi/utils/timer.h>

#include "radi/debug/debug_layer.h"
#include "radi/events/events.h"

namespace radi {

	class RD_API Application
	{
	private:
		static Application* s_instance;
	public:
		graphics::Window* window;
		debug::DebugLayer* m_DebugLayer;
	private:
		bool m_running, m_suspended;
		Timer* m_Timer;
		uint m_updatesPerSecond, m_framesPerSecond;

		const char* m_name;
		uint m_width, m_height;

		std::vector<graphics::Layer*> m_layerStack;
		std::vector<graphics::Layer*> m_overlayStack;
	public:
		Application(const char* name, uint width, uint height);
		virtual ~Application();

		virtual void Init();

		void PushLayer(graphics::Layer* layer);
		graphics::Layer* PopLayer();

		void PushOverlay(graphics::Layer* layer);
		graphics::Layer* PopOverlay();

		void Start();
		void Suspend();
		void Resume();
		void Stop();

		const uint GetFPS() const { return m_framesPerSecond; }
		const uint GetUPS() const { return m_updatesPerSecond; }

	private:
		void PlatformInit();
		void Run();

		void OnTick();
		void OnUpdate();
		void OnRender();
	private:
		void OnEvent(events::Event& event);
	public:
		inline static Application& GetApplication() { return *s_instance; }
	};


}