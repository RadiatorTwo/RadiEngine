#pragma once

#include <radi/graphics/layers/layer2d.h>
#include <radi/graphics/label.h>
#include <radi/graphics/sprite.h>
#include <radi/graphics/renderer2d.h>

#include <radi/events/Events.h>

class TestLayer : public radi::graphics::Layer2D
{
private:
	radi::graphics::Label* m_fps;
	radi::graphics::Label** debugInfo;
	radi::graphics::Sprite* m_mario;
	radi::graphics::Renderer2D* m_Renderer;
public:
	TestLayer();
	~TestLayer();

	void OnInit(radi::graphics::Renderer2D& renderer, radi::graphics::Shader& shader) override;

	void OnTick() override;
	void OnUpdate() override;
	
	bool OnKeyPressedEvent(radi::events::KeyPressedEvent& event);
	void OnEvent(radi::events::Event& event) override;

	void OnRender(radi::graphics::Renderer2D& renderer) override;
};