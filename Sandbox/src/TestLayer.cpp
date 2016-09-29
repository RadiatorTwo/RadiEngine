#include "TestLayer.h"

#include <radi/app/Application.h>

#include <radi/graphics/BatchRenderer2D.h>
#include <radi/graphics/shaders/shader_factory.h>
#include <radi/graphics/font_manager.h>
#include <radi/graphics/Sprite.h>

using namespace radi;
using namespace graphics;
using namespace events;
using namespace maths;

TestLayer::TestLayer()
	: Layer2D(ShaderFactory::DefaultShader(), mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f))
{
	m_Renderer = nullptr;
}

TestLayer::~TestLayer()
{

}

void TestLayer::OnInit(Renderer2D& renderer, Shader& shader)
{
	m_Renderer = &renderer;

	renderer.SetRenderTarget(RenderTarget::SCREEN);
	Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
	renderer.AddPostEffectsPass(new PostEffectsPass(Shader::FromFile("Horizontal Blur", "shaders/postfx.shader")));
	renderer.SetPostEffects(false);

	Texture::SetFilter(TextureFilter::NEAREST);
	m_mario = new Sprite(0.0f, 0.0f, 0.15f * 8, 0.2f * 8, new Texture("mario", "res/mario32.png"));


	for (float i = -16; i < 16.0f; i += 0.16f * 4)
	{
		Add(new Sprite(i, -9.0f, 0.16f * 4, 0.16f * 4, new Texture("ground_tile", "res/ground_tile.png")));
	}

	//for (float i = -16.0f; i < 16.0f; i += 5.12f * 4)
	//{
	//	Add(new Sprite(i, -9.0f + (0.16f * 4), 5.12f * 4, 4.32f * 4, new Texture("background", "res/background.png")));
	//}

	Add(m_mario);

	debugInfo = new Label*[10];
	debugInfo[0] = new Label("", -15.5f, 6.8f, 0xff000000);
	debugInfo[1] = new Label("", -15.5f, 5.8f, 0xff000000);
	Add(debugInfo[0]);
	Add(debugInfo[1]);

	Mask* mask = new Mask(new Texture("Mask", "res/mask.png"));
	mask->transform = mat4::Translate(vec3(-16.0f, -9.0f, 0.0f)) * mat4::Scale(vec3(32, 18, 1));
	// layer->SetMask(mask);
	SetMask(mask);
}

void TestLayer::OnTick()
{
	Application& app = Application::GetApplication();
	RADI_INFO(app.GetUPS(), " ups, ", app.GetFPS(), " fps");
}

void TestLayer::OnUpdate()
{
	//float speed = 0.15f;
	//if (m_window->IsKeyPressed(VK_LEFT))
	//	m_mario->position.x -= speed;
	//else if (m_window->IsKeyPressed(VK_RIGHT))
	//	m_mario->position.x += speed;

	//if (m_window->IsKeyPressed(VK_UP))
	//	m_mario->position.y += speed;
	//else if (m_window->IsKeyPressed(VK_DOWN))
	//	m_mario->position.y -= speed;
}

bool TestLayer::OnKeyPressedEvent(KeyPressedEvent& event)
{
	if (!m_Renderer)
		return false;

	Renderer2D& renderer = *m_Renderer;

	if (event.GetRepeat())
		return false;

	if (event.GetKeyCode() == RD_KEY_T)
	{
		renderer.SetRenderTarget(renderer.GetRenderTarget() == RenderTarget::SCREEN ? RenderTarget::BUFFER : RenderTarget::SCREEN);
		return true;
	}
	if (event.GetKeyCode() == RD_KEY_P)
	{
		renderer.SetPostEffects(!renderer.GetPostEffects());
		return true;
	}

	return false;
}

void TestLayer::OnEvent(radi::events::Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(METHOD(&TestLayer::OnKeyPressedEvent));
}

void TestLayer::OnRender(Renderer2D& renderer)
{
	debugInfo[0]->text = String("Target: ") + (renderer.GetRenderTarget() == RenderTarget::SCREEN ? "Screen" : "Buffer");
	debugInfo[1]->text = String("PostFX: ") + (renderer.GetPostEffects() ? "On" : "Off");
}