#include "TestLayer.h"

#include <app/Application.h>

#include <graphics/BatchRenderer2D.h>
#include <graphics/shaders/shader_factory.h>
#include <graphics/font_manager.h>
#include <graphics/Sprite.h>

using namespace radi;
using namespace graphics;
using namespace events;
using namespace maths;

TestLayer::TestLayer()
	: Layer2D(ShaderFactory::DefaultShader(), mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{

}

TestLayer::~TestLayer()
{

}

void TestLayer::OnInit(Renderer2D& renderer, Shader& shader)
{
	FontManager::get()->setScale(m_window->getWidth() / 32.0f, m_window->getHeight() / 18.0f);
	renderer.SetRenderTarget(RenderTarget::SCREEN);
	Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
	renderer.AddPostEffectsPass(new PostEffectsPass(Shader::FromFile("Horizontal Blur", "shaders/postfx.shader")));
	renderer.SetPostEffects(false);

	Texture::SetFilter(TextureFilter::NEAREST);
	m_mario = new Sprite(0.0f, 0.0f, 0.15f * 4, 0.2f * 4, new Texture("mario", "res/mario32.png"));
	Add(m_mario);

	for (float i = -16; i < 16.0f; i += 0.16f * 4)
	{
		Add(new Sprite(i, -9.0f, 0.16f * 4, 0.16f * 4, new Texture("ground_tile", "res/ground_tile.png")));
	}

	for (float i = -16.0f; i < 16.0f; i += 5.12f * 4)
	{
		Add(new Sprite(i, -9.0f + (0.16f * 4), 5.12f * 4, 4.32f * 4, new Texture("background", "res/background.png")));
	}

	m_fps = new Label("", -15.5f, 7.8f, 0xff000000);
	Add(m_fps);

	debugInfo = new Label*[10];
	debugInfo[0] = new Label("", -15.5f, 6.8f, 0xff000000);
	debugInfo[1] = new Label("", -15.5f, 5.8f, 0xff000000);
	Add(debugInfo[0]);
	Add(debugInfo[1]);
	
	//Mask* mask = new Mask(new Texture("Mask", "res/mask.png"));
	//mask->transform = mat4::translation(vec3(-16.0f, -9.0f, 0.0f)) * mat4::scale(vec3(32, 18, 1));
	// layer->SetMask(mask);
}

void TestLayer::OnTick()
{
	Application& app = Application::GetApplication();
	m_fps->text = std::to_string(app.GetFPS()) + " fps";
	RADI_INFO(app.GetUPS(), " ups, ", app.GetFPS(), " fps");
}

void TestLayer::OnUpdate()
{
	float speed = 0.15f;
	if (m_window->isKeyPressed(VK_LEFT))
		m_mario->position.x -= speed;
	else if (m_window->isKeyPressed(VK_RIGHT))
		m_mario->position.x += speed;

	if (m_window->isKeyPressed(VK_UP))
		m_mario->position.y += speed;
	else if (m_window->isKeyPressed(VK_DOWN))
		m_mario->position.y -= speed;
}

bool TestLayer::OnEvent(const radi::events::Event& event)
{
	return false;
}

void TestLayer::OnRender(Renderer2D& renderer)
{
	// TODO: Move this into OnEvent!
	if (m_window->isKeyTyped(VK_T))
		renderer.SetRenderTarget(renderer.GetRenderTarget() == RenderTarget::SCREEN ? RenderTarget::BUFFER : RenderTarget::SCREEN);
	if (m_window->isKeyTyped(VK_P))
		renderer.SetPostEffects(!renderer.GetPostEffects());

	debugInfo[0]->text = std::string("Target: ") + (renderer.GetRenderTarget() == RenderTarget::SCREEN ? "Screen" : "Buffer");
	debugInfo[1]->text = std::string("PostFX: ") + (renderer.GetPostEffects() ? "On" : "Off");
}