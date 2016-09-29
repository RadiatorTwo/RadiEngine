#pragma once

#include <radi.h>

class Test3D : public radi::graphics::Layer3D
{
private:
	radi::entity::Entity* m_Cube;
	radi::entity::Entity* m_Sphere;
	radi::entity::Entity* m_Plane;
	float m_rotation;
	bool m_setUniforms[2];
public:
	Test3D();
	~Test3D();

	void OnInit(radi::graphics::Renderer3D& renderer, radi::graphics::Scene& scene) override;

	void OnTick() override;
	void OnUpdate() override;
	void OnEvent(radi::events::Event& event) override;
};