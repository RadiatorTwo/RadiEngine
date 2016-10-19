#pragma once

#include <radi.h>

class Test2D : public radi::graphics::Layer2D
{
private:
	radi::graphics::Label** debugInfo;
	radi::graphics::Renderer2D* m_Renderer;
public:
	Test2D();
	~Test2D();

	void OnInit(radi::graphics::Renderer2D& renderer, radi::graphics::Material& material) override;

	void OnTick() override;
	void OnUpdate() override;

	bool OnKeyPressedEvent(radi::events::KeyPressedEvent& event);
	bool OnMousePressedEvent(radi::events::MousePressedEvent& event);
	void OnEvent(radi::events::Event& event) override;

	void OnRender(radi::graphics::Renderer2D& renderer) override;
};