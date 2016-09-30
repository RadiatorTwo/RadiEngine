#include "Test3D.h"

using namespace radi;
using namespace debug;
using namespace graphics;
using namespace maths;

using namespace events;
using namespace entity;
using namespace component;

using namespace API;

Test3D::Test3D()
	: Layer3D(rdnew Scene())
{
	m_MayaCamera = m_Scene->GetCamera();
	m_FPSCamera = rdnew FPSCamera(maths::mat4::Perspective(65.0f, 16.0f / 9.0f, 0.1f, 1000.0f));

	m_Rotation = 0.0f;
	m_SetUniforms[0] = true;
	m_SetUniforms[1] = true;

	mat4 result = mat4::Identity() * mat4::Identity();
}

Test3D::~Test3D()
{
}

vec3 g_CubeTransform(-10, 10, 0);
vec3 g_DaggerTransform(0, 20, 0);
vec4 g_SphereColor(0.0f, 0.0f, 0.0f, 1.0f);
vec3 g_SphereSpecularColor(1.0f, 1.0f, 0.6f);

float g_DaggerGloss = 0.5f;

Shader* shadowPassShader;
FramebufferDepth* g_DepthBuffer;
TextureDepth* g_ShadowMap;

String materialInputs[5] =
{
	"CastIron",
	"WornWood",
	"GunMetal",
	"ABSRed",
	"Custom"
};

enum Materials : uint
{
	CAST_IRON = 0,
	WORN_WOOD,
	GUN_METAL,
	ABS_RED,
	CUSTOM
};

void Test3D::OnInit(Renderer3D& renderer, Scene& scene)
{
	// Enable this to use FPS camera
	// scene.SetCamera(m_FPSCamera);

	Timer timer;
	String files[6] =
	{
		"res/skybox/sky_xp.png",
		"res/skybox/sky_xn.png",
		"res/skybox/sky_yp.png",
		"res/skybox/sky_yn.png",
		"res/skybox/sky_zp.png",
		"res/skybox/sky_zn.png"
	};

	String environmentFiles[11] =
	{
		"res/pbr/cubemap/CubeMap0.tga",
		"res/pbr/cubemap/CubeMap1.tga",
		"res/pbr/cubemap/CubeMap2.tga",
		"res/pbr/cubemap/CubeMap3.tga",
		"res/pbr/cubemap/CubeMap4.tga",
		"res/pbr/cubemap/CubeMap5.tga",
		"res/pbr/cubemap/CubeMap6.tga",
		"res/pbr/cubemap/CubeMap7.tga",
		"res/pbr/cubemap/CubeMap8.tga",
		"res/pbr/cubemap/CubeMap9.tga",
		"res/pbr/cubemap/CubeMap10.tga"
	};

	TextureCube* environment = TextureCube::CreateFromVCross(environmentFiles, 11);
	Shader* skybox = Shader::CreateFromFile("Skybox", String("shaders/Skybox") + (API::Context::GetRenderAPI() == RenderAPI::OPENGL ? ".shader" : ".hlsl"));
	Material* skyboxMaterial = rdnew Material(skybox);
	skyboxMaterial->SetRenderFlag(Material::RenderFlags::DISABLE_DEPTH_TEST);
	skybox->Bind();
	m_SkyboxMaterial = rdnew MaterialInstance(skyboxMaterial);
	m_SkyboxMaterial->SetTexture("u_EnvironmentMap", environment);
	Entity* skyboxEntity = rdnew Entity(MeshFactory::CreateQuad(-1, -1, 2, 2, m_SkyboxMaterial));
	m_Scene->Add(skyboxEntity);

	Shader* pbrShader = Shader::CreateFromFile("AdvancedLighting", String("shaders/AdvancedLighting") + (API::Context::GetRenderAPI() == RenderAPI::OPENGL ? ".shader" : ".hlsl"));
	ShaderManager::Add(pbrShader);
	PBRMaterial* material = rdnew PBRMaterial(pbrShader);

	PBRMaterial* castIron = rdnew PBRMaterial(pbrShader);
	castIron->SetEnviromentMap(environment);
	{
		String path = materialInputs[CAST_IRON] + "/" + materialInputs[CAST_IRON];
		castIron->SetAlbedoMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Albedo.tga"));
		castIron->SetSpecularMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Specular.tga"));
		castIron->SetGlossMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Gloss.tga"));
		castIron->SetNormalMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Normal.tga"));
	}
	m_Materials.push_back(castIron);

	PBRMaterial* wornWood = rdnew PBRMaterial(pbrShader);
	wornWood->SetEnviromentMap(environment);
	{
		String path = materialInputs[WORN_WOOD] + "/" + materialInputs[WORN_WOOD];
		wornWood->SetAlbedoMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Albedo.tga"));
		wornWood->SetSpecularMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Specular.tga"));
		wornWood->SetGlossMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Gloss.tga"));
		wornWood->SetNormalMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Normal.tga"));
	}
	m_Materials.push_back(wornWood);

	PBRMaterial* gunMetal = rdnew PBRMaterial(pbrShader);
	gunMetal->SetEnviromentMap(environment);
	{
		String path = materialInputs[GUN_METAL] + "/" + materialInputs[GUN_METAL];
		gunMetal->SetAlbedoMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Albedo.tga"));
		gunMetal->SetSpecularMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Specular.tga"));
		gunMetal->SetGlossMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Gloss.tga"));
		gunMetal->SetNormalMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Normal.tga"));
	}
	m_Materials.push_back(gunMetal);


	PBRMaterial* absRed = rdnew PBRMaterial(pbrShader);
	absRed->SetEnviromentMap(environment);
	{
		String path = materialInputs[ABS_RED] + "/" + materialInputs[ABS_RED];
		absRed->SetAlbedoMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Albedo.tga"));
		absRed->SetSpecularMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Specular.tga"));
		absRed->SetGlossMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Gloss.tga"));
		absRed->SetNormalMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Normal.tga"));
	}
	m_Materials.push_back(absRed);

	PBRMaterial* custom = rdnew PBRMaterial(pbrShader);
	custom->SetEnviromentMap(environment);
	{
		String path = materialInputs[CUSTOM] + "/" + materialInputs[CUSTOM];
		custom->SetAlbedoMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Albedo.tga"));
		custom->SetSpecularMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Specular.tga"));
		custom->SetGlossMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Gloss.tga"));
		custom->SetNormalMap(Texture2D::CreateFromFile("res/pbr/" + path + "_Normal.tga"));
	}
	m_Materials.push_back(custom);

	// Texture::SetLoadParameters(0);
	m_DaggerMaterial = rdnew PBRMaterial(pbrShader);
	m_DaggerMaterial->SetEnviromentMap(environment);
	{
		TextureLoadOptions options(false, true);
		m_DaggerMaterial->SetAlbedoMap(Texture2D::CreateFromFile("res/Dagger/Textures/Dagger_Albedo.tga", options));
		m_DaggerMaterial->SetSpecularMap(Texture2D::CreateFromFile("res/Dagger/Textures/Dagger_Specular.tga", options));
		m_DaggerMaterial->SetGlossMap(Texture2D::CreateFromFile("res/Dagger/Textures/Dagger_Gloss.tga", options));
		m_DaggerMaterial->SetNormalMap(Texture2D::CreateFromFile("res/Dagger/Textures/Dagger_Normals.tga", options));
	}
	
	Model* daggerModel = rdnew Model("res/models/Dagger.spm", rdnew MaterialInstance(m_DaggerMaterial));
	m_Dagger = rdnew Entity(daggerModel->GetMesh(), mat4::Translate(g_DaggerTransform));
	m_Scene->Add(m_Dagger);

	PBRMaterial* cubeMaterial = rdnew PBRMaterial(pbrShader);
	cubeMaterial->SetEnviromentMap(environment);
	Model* cubeModel = rdnew Model("res/models/RoundedCube.spm", rdnew MaterialInstance(cubeMaterial));
	m_Cube = rdnew Entity(cubeModel->GetMesh(), mat4::Rotate(90.0f, vec3(0, 0, 1)) * mat4::Translate(g_CubeTransform));
	m_Scene->Add(m_Cube);

	Model* sphereModel = rdnew Model("res/models/Sphere.spm");

	// Plastics
	for (uint x = 0; x < 10; x++)
	{
		float xx = x * 10.0f;
		float zz = 3.0f;

		float roughness = x / 10.0f;
		vec3 spec(0.04f);
		vec4 diffuse(vec3(1.0f, 0.0f, 0.0f), 1.0f);

		PBRMaterialInstance* m = rdnew PBRMaterialInstance(m_Materials[CAST_IRON]);
		m->SetAlbedo(diffuse);
		m->SetSpecular(spec);
		m->SetGloss(1.0f - roughness);
		m->UsingNormalMap(false);

		Mesh* mesh = rdnew Mesh(sphereModel->GetMesh());
		mesh->SetMaterial(m);

		Entity* sphere = rdnew Entity(mesh, mat4::Translate(vec3(-60 + xx, 2.5f, 90 + zz)) * mat4::Scale(vec3(2.0f)));
		m_Spheres.push_back(sphere);
		m_Scene->Add(sphere);
	}

	// Metals
	for (uint x = 0; x < 10; x++)
	{
		float xx = x * 10.0f;
		float zz = 0;

		float roughness = x / 10.0f;
		vec3 spec(1.0f);
		vec4 diffuse(0.0f, 0.0f, 0.0f, 1.0f);

		PBRMaterialInstance* m = rdnew PBRMaterialInstance(m_Materials[CAST_IRON]);
		m->SetAlbedo(diffuse);
		m->SetSpecular(spec);
		m->SetGloss(1.0f - roughness);
		m->UsingNormalMap(false);

		Mesh* mesh = rdnew Mesh(sphereModel->GetMesh());
		mesh->SetMaterial(m);

		Entity* sphere = rdnew Entity(mesh, mat4::Translate(vec3(-60 + xx, 2.5f, 80 + zz)) * mat4::Scale(vec3(2.0)));
		m_Spheres.push_back(sphere);
		m_Scene->Add(sphere);
	}

	m_Plane = rdnew Entity(MeshFactory::CreatePlane(128, 128, vec3(0, 1, 0), rdnew PBRMaterialInstance(m_Materials[CUSTOM])));
	m_Scene->Add(m_Plane);

	LightSetup* lights = rdnew LightSetup();
	m_Light = rdnew Light(vec3(0.8f));
	lights->Add(m_Light);
	m_Scene->PushLightSetup(lights);

	DebugMenu::Add("Cube", &g_CubeTransform, -100.0f, 100.0f);
	DebugMenu::Add("Light Direction", &lights->GetLights()[0]->direction, -1.0f, 1.0f);
	DebugMenu::Add("Light Intensity", &lights->GetLights()[0]->intensity, 0, 100);
	DebugMenu::Add("Dagger", &g_DaggerTransform, -50, 50);
	DebugMenu::Add("Dagger Gloss", &g_DaggerGloss, 0.0f, 1.0f);

	// shadowPassShader = Shader::CreateFromFile("Shadow", "shaders/ShadowPass.shader");
	// g_DepthBuffer = FramebufferDepth::Create(2048, 2048);
	// g_ShadowMap = (TextureDepth*)g_DepthBuffer->GetTexture();

	for (uint i = 0; i < 4; i++)
	{
		// m_Materials[i]->SetTexture(g_ShadowMap, 6);
		// m_Materials[i]->SetUniform("u_ShadowMap", 6);
	}

	RADI_INFO("Init took ", timer.ElapsedMillis(), " ms");
}

void Test3D::OnTick()
{
	Application& app = Application::GetApplication();
	RADI_INFO(app.GetUPS(), " ups, ", app.GetFPS(), " fps");
}

void Test3D::OnUpdate()
{
	TransformComponent* cubeTransform = m_Cube->GetComponent<TransformComponent>();

	mat4 transform = mat4::Translate(vec3(0, 2.5f, 0)) * mat4::Rotate(m_Rotation, vec3(1, 0, 0)) * mat4::Rotate(m_Rotation, vec3(0, 1, 0)) * mat4::Rotate(m_Rotation, vec3(0, 0, 1));
	cubeTransform->transform = mat4::Translate(g_CubeTransform) * transform * mat4::Scale(vec3(1.4f, 1.4f, 1.4f));

	TransformComponent* dagger = m_Dagger->GetComponent<TransformComponent>();
	dagger->transform = mat4::Translate(g_DaggerTransform);

	for (Entity* sphere : m_Spheres)
	{
		TransformComponent* sphereTransform = sphere->GetComponent<TransformComponent>();
		//	sphereTransform->transform = sphereTransform->transform * mat4::Rotate(1.0f, vec3(0, 1, 0));
	}

	// Still OpenGL maths style (column-major)
	mat4 vp = m_Scene->GetCamera()->GetProjectionMatrix() * m_Scene->GetCamera()->GetViewMatrix();
	m_SkyboxMaterial->SetUniform("invViewProjMatrix", mat4::Invert(vp));
}

void Test3D::OnRender(Renderer3D& renderer)
{
#if 0
	mat4 depthProjectionMatrix = mat4::Orthographic(-10, 10, -10, 10, -10, 20);
	mat4 depthViewMatrix = mat4::LookAt(vec3(0.5f, 0.5f, 2.0f), vec3(), vec3::Up());
	mat4 depthMVP = depthProjectionMatrix * depthViewMatrix;

	g_DepthBuffer->Bind();
	g_DepthBuffer->Clear();
	renderer.Begin();
	for (uint i = 0; i < m_Scene->GetEntities().size(); i++)
	{
		Entity* e = m_Scene->GetEntities()[i];
		RenderCommand command;
		command.mesh = e->GetComponent<MeshComponent>()->mesh;
		command.shader = shadowPassShader;
		command.uniforms.push_back({ "ml_matrix", (byte*)&e->GetComponent<TransformComponent>()->transform });
		command.uniforms.push_back({ "u_DepthMatrix", (byte*)&depthMVP });
		renderer.Submit(command);
	}
	renderer.End();
	renderer.Present();

	g_DepthBuffer->Unbind();

	float elements[4 * 4] = {
		0.5, 0.0, 0.0, 0.0,
		0.0, 0.5, 0.0, 0.0,
		0.0, 0.0, 0.5, 0.0,
		0.5, 0.5, 0.5, 1.0
	};
	mat4 biasMatrix(elements);
	mat4 depthBiasMVP = biasMatrix * depthMVP;

	for (Material* material : m_Materials)
		material->SetUniform("u_DepthBiasMVP", depthBiasMVP);

#endif

	//DebugLayer::DrawTexture(m_DaggerMaterial->GetGlossMap());
	Layer3D::OnRender(renderer);
}

void Test3D::OnEvent(Event& event)
{
	if (event.GetType() == Event::Type::KEY_PRESSED)
	{
		KeyPressedEvent* kpe = (KeyPressedEvent*)&event;
		if (kpe->GetRepeat() == 0)
		{
			switch (kpe->GetKeyCode())
			{
			case RD_KEY_R:
				ShaderManager::Reload("AdvancedLighting");
				break;
			case RD_KEY_C:
				m_Scene->SetCamera(m_Scene->GetCamera() == m_MayaCamera ? m_FPSCamera : m_MayaCamera);
				break;
			}
		}
	}
	Layer::OnEvent(event);
}
