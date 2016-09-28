#pragma once

#include <radi/app/Application.h>
#include <radi/maths/maths.h>

#include <radi/graphics/mesh_factory.h>
#include <radi/graphics/layers/layer3D.h>
#include <radi/graphics/shaders/shader_factory.h>
#include <radi/graphics/model.h>

#include <radi/entity/entity.h>
#include <radi/entity/component/components.h>

class Test3D : public radi::graphics::Layer3D
{
private:
	radi::entity::Entity* m_Cube;
	radi::entity::Entity* m_Sphere;
	float m_rotation;
	bool m_setUniforms[2];
public:
	Test3D();
	~Test3D();

	void OnInit(radi::graphics::Renderer3D& renderer, radi::graphics::Scene& scene) override;

	void OnTick() override;
	void OnUpdate() override;
	bool OnEvent(const radi::events::Event& event) override;
};