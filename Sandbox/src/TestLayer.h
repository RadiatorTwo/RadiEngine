#pragma once

#include <graphics/layers/Layer2D.h>
#include <events/Event.h>
#include <graphics/Label.h>
#include <graphics/Renderer2D.h>

class TestLayer : public radi::graphics::Layer2D
{
private:
	radi::graphics::Label* m_fps;
	radi::graphics::Label** debugInfo;
public:
	TestLayer();
	~TestLayer();

	void OnInit(radi::graphics::Renderer2D& renderer, radi::graphics::Shader& shader) override;

	void OnTick() override;
	void OnUpdate() override;
	bool OnEvent(const radi::events::Event& event) override;
	void OnRender(radi::graphics::Renderer2D& renderer) override;
};