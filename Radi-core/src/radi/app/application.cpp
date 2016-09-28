#include "radi/rd.h"
#include "application.h"

namespace radi {

	using namespace graphics;

	Application* Application::s_instance = nullptr;

	void Application::Init()
	{
		PlatformInit();

		m_DebugLayer = new debug::DebugLayer();
		m_DebugLayer->Init();
	}

	void Application::PushLayer(Layer* layer)
	{
		m_layerStack.push_back(layer);
		layer->Init();
	}

	Layer* Application::PopLayer()
	{
		Layer* layer = m_layerStack.back();
		m_layerStack.pop_back();
		return layer;
	}

	void Application::PushOverlay(Layer* layer)
	{
		m_overlayStack.push_back(layer);
		layer->Init();
	}

	Layer* Application::PopOverlay()
	{
		Layer* layer = m_overlayStack.back();
		m_overlayStack.pop_back();
		return layer;
	}

	void Application::OnEvent(events::Event& event)
	{
		m_DebugLayer->OnEvent(event);
		if (event.IsHandled()) // TODO(Yan): Maybe this shouldn't happen
			return;

		for (int i = m_overlayStack.size() - 1; i >= 0; i--)
		{
			m_overlayStack[i]->OnEvent(event);
			if (event.IsHandled())
				return;
		}

		for (int i = m_layerStack.size() - 1; i >= 0; i--)
		{
			m_layerStack[i]->OnEvent(event);
			if (event.IsHandled())
				return;
		}
	}

	void Application::OnTick()
	{
		m_DebugLayer->OnTick();

		for (uint i = 0; i < m_overlayStack.size(); i++)
			m_overlayStack[i]->OnTick();

		for (uint i = 0; i < m_layerStack.size(); i++)
			m_layerStack[i]->OnTick();
	}

	void Application::OnUpdate()
	{
		m_DebugLayer->OnUpdate();

		for (uint i = 0; i < m_overlayStack.size(); i++)
			m_overlayStack[i]->OnUpdate();

		for (uint i = 0; i < m_layerStack.size(); i++)
			m_layerStack[i]->OnUpdate();
	}

	void Application::OnRender()
	{
		for (uint i = 0; i < m_layerStack.size(); i++)
		{
			if (m_layerStack[i]->IsVisible())
				m_layerStack[i]->OnRender();

		}

		for (uint i = 0; i < m_overlayStack.size(); i++)
		{
			if (m_overlayStack[i]->IsVisible())
				m_overlayStack[i]->OnRender();

		}

		Layer2D* debugLayer = (Layer2D*)m_DebugLayer;
		if (debugLayer->IsVisible())
			debugLayer->OnRender();
	}

}