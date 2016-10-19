#pragma once

#include <radi.h>

class Sponza : public radi::graphics::Layer3D
{
private:
	radi::graphics::Camera* m_MayaCamera;
	radi::graphics::Camera* m_FPSCamera;
	radi::graphics::MaterialInstance* m_SkyboxMaterial;
	radi::graphics::Light* m_Light;

public:
	Sponza();
	~Sponza();

	void OnInit(radi::graphics::Renderer3D& renderer, radi::graphics::Scene& scene) override;

	void OnTick() override;
	void OnUpdate() override;
	void OnEvent(radi::events::Event& event) override;

	void OnRender(radi::graphics::Renderer3D& renderer);
};