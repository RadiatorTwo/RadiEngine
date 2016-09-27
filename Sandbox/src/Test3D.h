#pragma once

#include <app/Application.h>
#include <maths/maths.h>

#include <graphics/mesh_factory.h>
#include <graphics/layers/Layer3D.h>
#include <graphics/shaders/shader_factory.h>

class Test3D : public radi::graphics::Layer3D
{
private:
	radi::graphics::Mesh* m_Cube;
	radi::graphics::Material* m_Material;
	float m_Rotation;
public:
	Test3D();
	~Test3D();

	void OnInit(radi::graphics::Renderer3D& renderer, radi::graphics::Scene& scene) override;

	void OnTick() override;
	void OnUpdate() override;
	bool OnEvent(const radi::events::Event& event) override;
};