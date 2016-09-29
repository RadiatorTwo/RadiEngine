#include "Test3D.h"

using namespace radi;
using namespace debug;
using namespace radi::graphics;
using namespace maths;

using namespace entity;
using namespace component;

Test3D::Test3D()
	: Layer3D(new Scene())
{
	m_rotation = 0.0f;
	m_setUniforms[0] = true;
	m_setUniforms[1] = true;
}

Test3D::~Test3D()
{
}

float xTransform = -4.0f;
float sSize = 4.0f;

void Test3D::OnInit(Renderer3D& renderer, Scene& scene)
{
	Material* material = new Material(Shader::FromFile("Scene", "shaders/scene.shader"));

	m_Cube = new Entity();
	Model* cubeModel = new Model("res/cube.obj", new MaterialInstance(material));
	m_Cube->AddComponent(new MeshComponent(cubeModel->GetMesh()));
	m_Cube->AddComponent(new TransformComponent(mat4::Identity()));

	m_Sphere = new Entity();
	Model* sphereModel = new Model("res/sphere.obj", new MaterialInstance(material));
	m_Sphere->AddComponent(new MeshComponent(sphereModel->GetMesh()));
	m_Sphere->AddComponent(new TransformComponent(mat4::Identity()));

	m_Plane = new Entity();
	m_Plane->AddComponent(new MeshComponent(meshfactory::CreatePlane(32, 32, vec3(0, 1, 0), new MaterialInstance(material))));
	m_Plane->AddComponent(new TransformComponent(mat4::Identity()));

	m_scene->Add(m_Cube);
	m_scene->Add(m_Sphere);
	m_scene->Add(m_Plane);

	LightSetup* lights = new LightSetup();
	lights->Add(new Light{ vec3(0, 10, 0), 10.0f, vec4(1, 1, 1, 1) });
	m_scene->PushLightSetup(lights);

	DebugMenu::Init();
	DebugMenu::Add("Cube X", &xTransform, -20.0f, 20.0f);
	DebugMenu::Add("Sphere Size", &sSize, -20.0f, 20.0f);
	DebugMenu::Add("Light Atten.", &lights->GetLights()[0]->position.z, 0, 40);
}

void Test3D::OnTick()
{
	/*Application& app = Application::GetApplication();
	RADI_INFO(app.GetUPS(), " ups, ", app.GetFPS(), " fps");*/
}


void Test3D::OnUpdate()
{
	TransformComponent* cubeTransform = m_Cube->GetComponent<TransformComponent>();
	TransformComponent* sphereTransform = m_Sphere->GetComponent<TransformComponent>();

	mat4 transform = mat4::Translate(vec3(0, 2.5f, 0)) * mat4::Rotate(m_rotation, vec3(1, 0, 0)) * mat4::Rotate(m_rotation, vec3(0, 1, 0)) * mat4::Rotate(m_rotation, vec3(0, 0, 1));
	//cubeTransform->transform = mat4::Translate(vec3(xTransform, 0, 0)) * transform * mat4::Scale(vec3(1.4f, 1.4f, 1.4f));
	cubeTransform->transform = mat4::Translate(vec3(0, 0, 0)) * transform * mat4::Scale(vec3(xTransform, xTransform, xTransform));
	sphereTransform->transform = mat4::Translate(vec3(4, 0, 0)) * transform * mat4::Scale(vec3(sSize, sSize, sSize));
	m_rotation++;
}

void Test3D::OnEvent(radi::events::Event& event)
{
}