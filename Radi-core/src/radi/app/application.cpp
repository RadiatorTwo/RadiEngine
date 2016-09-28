#include "application.h"

namespace radi {

	using namespace graphics;

	Application* Application::s_instance = nullptr;

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

	void Application::OnTick()
	{
		for (uint i = 0; i < m_layerStack.size(); i++)
			m_layerStack[i]->OnTick();
	}

	void Application::OnUpdate()
	{
		for (uint i = 0; i < m_layerStack.size(); i++)
			m_layerStack[i]->OnUpdate();
	}

	void Application::OnRender()
	{
		for (uint i = 0; i < m_layerStack.size(); i++)
			m_layerStack[i]->OnRender();
	}

}