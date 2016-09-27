#pragma once

#include <graphics/layers/layer2d.h>
#include <events/event.h>
#include <graphics/label.h>
#include <graphics/sprite.h>
#include <graphics/renderer2d.h>

class TestLayer : public radi::graphics::Layer2D
{
private:
	radi::graphics::Label* m_fps;
	radi::graphics::Label** debugInfo;
	radi::graphics::Sprite* m_mario;
public:
	TestLayer();
	~TestLayer();

	void OnInit(radi::graphics::Renderer2D& renderer, radi::graphics::Shader& shader) override;

	void OnTick() override;
	void OnUpdate() override;
	bool OnEvent(const radi::events::Event& event) override;
	void OnRender(radi::graphics::Renderer2D& renderer) override;
};