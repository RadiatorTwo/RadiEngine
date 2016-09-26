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
	// m_Window->SetVsync(false);

	FontManager::get()->setScale(m_window->getWidth() / 32.0f, m_window->getHeight() / 18.0f);
	renderer.SetRenderTarget(RenderTarget::BUFFER);
	renderer.AddPostEffectsPass(new PostEffectsPass(Shader::FromFile("shaders/postfx.vert", "shaders/postfx.frag")));
	renderer.SetPostEffects(false);

	Texture::SetFilter(TextureFilter::NEAREST);
	Add(new Sprite(0.0f, 0.0f, 0.15f * 8, 0.2f * 8, new Texture("mario", "res/mario32.png")));
	Add(new Sprite(0.0f, 0.0f, 8, 8, new Texture("test", "res/test2.png")));
	Add(new Sprite(-8.0f, -8.0f, 6, 6, 0xffff00ff));

	m_fps = new Label("", -15.5f, 7.8f, 0xffffffff);
	Add(m_fps);

	debugInfo = new Label*[10];
	debugInfo[0] = new Label("", -15.5f, 6.8f, 0xffffffff);
	debugInfo[1] = new Label("", -15.5f, 5.8f, 0xffffffff);
	Add(debugInfo[0]);
	Add(debugInfo[1]);

	Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
	Mask* mask = new Mask(new Texture("Mask", "res/mask.png"));
	mask->transform = mat4::translation(vec3(-16.0f, -9.0f, 0.0f)) * mat4::scale(vec3(32, 18, 1));
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