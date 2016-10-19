#pragma once

#include <radi.h>

class Test3D : public radi::graphics::Layer3D
{
private:
	radi::graphics::Camera* m_MayaCamera;
	radi::graphics::Camera* m_FPSCamera;

	radi::entity::Entity* m_Cube;
	std::vector<radi::entity::Entity*> m_Spheres;
	radi::entity::Entity* m_Plane;
	radi::entity::Entity* m_Dagger;
	radi::graphics::PBRMaterial* m_DaggerMaterial;
	radi::graphics::MaterialInstance* m_SkyboxMaterial;
	radi::graphics::Light* m_Light;
	float m_Rotation;
	bool m_SetUniforms[2];
	std::vector<radi::graphics::PBRMaterial*> m_Materials;
public:
	Test3D();
	~Test3D();

	void OnInit(radi::graphics::Renderer3D& renderer, radi::graphics::Scene& scene) override;

	void OnTick() override;
	void OnUpdate() override;
	void OnEvent(radi::events::Event& event) override;

	void OnRender(radi::graphics::Renderer3D& renderer);
};