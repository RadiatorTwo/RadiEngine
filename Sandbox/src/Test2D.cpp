#include "Test2D.h"

using namespace radi;
using namespace graphics;
using namespace events;
using namespace entity;
using namespace component;
using namespace maths;
using namespace API;

Test2D::Test2D()
	: Layer2D(rdnew Scene2D(mat4::Orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f)))
{
	m_Renderer = nullptr;
}

Test2D::~Test2D()
{

}

static float speed = 0.1f;
int backgroundCounter = 0;
int backgroundIndex = 1;

float dx = 0.01f;
float dy = 0.0f;
float gravity = 0.0005f;
float drag = 0.001f;
float jumpHeight = 0.1f;

void Test2D::OnInit(Renderer2D& renderer, Material& material)
{
	m_Renderer = &renderer;

	Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
	renderer.SetRenderTarget(RenderTarget::SCREEN);
	//renderer.AddPostEffectsPass(new PostEffectsPass(Shader::CreateFromFile("Horizontal Blur", "shaders/postfx.shader")));
	renderer.SetPostEffects(false);

	TextureParameters params(TextureFilter::NEAREST);
	//Add(new Sprite(0.0f, 0.0f, 4, 4, Texture2D::CreateFromFile("Tex", "res/tb.png", params)));

	m_texBackground1 = Texture2D::CreateFromFile("res/MarioGame/Background/Ghost1.png", params);
	m_texBackground2 = Texture2D::CreateFromFile("res/MarioGame/Background/Ghost2.png", params);
	m_texBackground3 = Texture2D::CreateFromFile("res/MarioGame/Background/Ghost3.png", params);

	m_texGroundTileLeft = Texture2D::CreateFromFile("res/MarioGame/Tiles/Ghost/GroundLeft.png", params);
	m_texGroundTileMiddle = Texture2D::CreateFromFile("res/MarioGame/Tiles/Ghost/GroundMiddle.png", params);
	m_texGroundTileRight = Texture2D::CreateFromFile("res/MarioGame/Tiles/Ghost/GroundRight.png", params);

	int count = 0;
	float widthBackground = 5.12f * 2;

	float position = -16.0f;
	for (float i = -16.0f; i < 16.0f; i += widthBackground)
	{
		m_backgroundArray.push_back(new Sprite(i + widthBackground, 0, 5.12f * 2, 4.32f * 2, m_texBackground1));
		Add(m_backgroundArray[count]);
		count++;
	}

	count = 0;
	float widthGround = 0.16f * 2;

	for (float i = -16.0f; i < 16.0f; i += widthGround)
	{
		m_groundTileArray.push_back(new Sprite(i + widthGround, -9.0f + (0.16f * 4), 0.16f * 2, 0.16f * 2, m_texGroundTileMiddle));
		Add(m_groundTileArray[count]);
		count++;
	}

	m_texMarioBigStill = Texture2D::CreateFromFile("res/MarioGame/Mario/MarioBigStill.png", params);
	m_texMarioBigWalk = Texture2D::CreateFromFile("res/MarioGame/Mario/MarioBigWalk.png", params);
	m_texMarioBigRun = Texture2D::CreateFromFile("res/MarioGame/Mario/MarioBigRun.png", params);

	m_marioSprite = rdnew Sprite(0.0f, 0.0f, 0.15f * 2, 0.28f * 2, m_texMarioBigStill);
	m_mario = rdnew Entity(m_marioSprite);
	m_Scene->Add(m_mario);

	debugInfo = new Label*[10];
	debugInfo[0] = rdnew Label("", -15.5f, 8.5f, 0xffffffff);
	debugInfo[1] = rdnew Label("", -15.5f, 7.5f, 0xffffffff);
	debugInfo[2] = rdnew Label("", -15.5f, 6.5f, 0xffffffff);
	debugInfo[3] = rdnew Label("", -15.5f, 5.5f, 0xffffffff);
	debugInfo[4] = rdnew Label("", -15.5f, 4.5f, 0xffffffff);
	Add(debugInfo[0]);
	Add(debugInfo[1]);
	Add(debugInfo[2]);
	Add(debugInfo[3]);
	Add(debugInfo[4]);

	debug::DebugMenu::Add("Mario Speed X", &dx, 0.01f, 0.1f);
	debug::DebugMenu::Add("Gravity", &gravity, 0.0001f, 0.001f);
	debug::DebugMenu::Add("Drag", &drag, 0.001f, 0.1f);
	debug::DebugMenu::Add("Jump Height", &jumpHeight, 0.1f, 1.0f);

	/*Mask* mask = new Mask(Texture2D::CreateFromFile("Mask", "res/mask.png"));
	mask->transform = mat4::Translate(vec3(-16.0f, -9.0f, 0.0f)) * mat4::Scale(vec3(32, 18, 1));
	SetMask(mask);*/

	/*for (int i = 0; i < 100; i++)
	{
		Entity* entity = rdnew Entity(rdnew Sprite(0.0f, 9.0f, s_BoxSize, s_BoxSize, vec4((rand() % 1000) / 1000.0f, 0.5f, 0.5f, 1.0f)));
		Physics2DComponent& p = entity->CreateComponent<Physics2DComponent>();
		m_Scene->Add(entity);

		p.ApplyForce(((rand() % 1000) - 500) * 0.005f);
	}*/
}

void Test2D::OnTick()
{
	using namespace radi::internal;

	Application& app = Application::GetApplication();
	RADI_INFO(app.GetUPS(), " ups, ", app.GetFPS(), " fps");

	debugInfo[2]->SetText("Total Allocs: " + StringFormat::ToString(MemoryManager::Get()->GetMemoryStats().totalAllocations));
	debugInfo[3]->SetText("Total Allocated: " + MemoryManager::BytesToString(MemoryManager::Get()->GetMemoryStats().totalAllocated));
	debugInfo[4]->SetText("Total Freed: " + MemoryManager::BytesToString(MemoryManager::Get()->GetMemoryStats().totalFreed));
}

void Test2D::OnUpdate(const Timestep& ts)
{
	AABB mario = m_marioSprite->GetBoundingBox();
	vec2 marioPosition = m_marioSprite->GetPosition();

	if (Input::IsKeyPressed(RD_KEY_LEFT))
	{
		marioPosition.x -= dx * ts.GetMillis();
	}
	if (Input::IsKeyPressed(RD_KEY_RIGHT))
	{
		marioPosition.x += dx * ts.GetMillis();
	}

	/*if (marioPosition.x > 16.0f - mario.GetSize().x)
	{
		marioPosition.x = 16.0f - mario.GetSize().x;
		dx = -dx;
	}
	else if (marioPosition.x < -16.0f)
	{
		marioPosition.x = -16.0f;
		dx = -dx;
	}*/

	dy -= gravity * ts.GetMillis();
	marioPosition.y += dy;
	if (marioPosition.y < -9.0f + mario.GetSize().y)
	{
		marioPosition.y = -9.0f + mario.GetSize().y;
		dy = 0.0f;
	}
	if (Input::IsKeyPressed(RD_KEY_UP) && marioPosition.y == -9.0f + mario.GetSize().y)
	{
		dy = jumpHeight;
	}
	if (!Input::IsKeyPressed(RD_KEY_UP) && dy > 0)
	{
		dy -= drag * ts.GetMillis();
	}

	/*bool intersects = false;
	for (int i = 0; i < m_groundTileArray.size(); i++)
	{
		AABB tile = m_groundTileArray[i]->GetBoundingBox();
		if (tile.Intersects(mario))
		{
			intersects = true;
			break;
		}
	}

	if (!intersects)
	{
		marioPosition.y -= gravity;
	}*/

	m_marioSprite->SetPosition(marioPosition);

	backgroundCounter++;
	if (backgroundCounter == 15)
	{
		if (backgroundIndex == 3)
		{
			backgroundIndex = 1;
		}
		else
		{
			backgroundIndex++;
		}

		for (int i = 0; i < m_backgroundArray.size(); i++)
		{
			switch (backgroundIndex)
			{
			case 1:
				m_backgroundArray[i]->SetTexture(m_texBackground1);
				break;
			case 2:
				m_backgroundArray[i]->SetTexture(m_texBackground2);
				break;
			case 3:
				m_backgroundArray[i]->SetTexture(m_texBackground3);
				break;
			}
		}

		backgroundCounter = 0;
	}

	/*if (Input::IsKeyPressed(RD_KEY_LEFT))
	{
		for (int i = 0; i < m_backgroundArray.size(); i++)
		{
			vec2 pos = m_backgroundArray[i]->GetPosition();
			pos.x += speed;
			m_backgroundArray[i]->SetPosition(pos);
		}

		for (int i = 0; i < m_groundTileArray.size(); i++)
		{
			vec2 pos = m_groundTileArray[i]->GetPosition();
			pos.x += speed;
			m_groundTileArray[i]->SetPosition(pos);
		}
	}
	else if (Input::IsKeyPressed(RD_KEY_RIGHT))
	{
		for (int i = 0; i < m_backgroundArray.size(); i++)
		{
			vec2 pos = m_backgroundArray[i]->GetPosition();
			pos.x -= speed;
			m_backgroundArray[i]->SetPosition(pos);
		}

		for (int i = 0; i < m_groundTileArray.size(); i++)
		{
			vec2 pos = m_groundTileArray[i]->GetPosition();
			pos.x -= speed;
			m_groundTileArray[i]->SetPosition(pos);
		}

		if (m_groundTileArray[m_groundTileArray.size()]->GetPosition().x + 0.8f < 16.0f)
		{
			vec2 posLastTile = m_groundTileArray[m_groundTileArray.size()]->GetPosition();

			m_groundTileArray.erase(m_groundTileArray.begin());

			m_groundTileArray.push_back(rdnew Sprite(posLastTile.x + 0.16f, posLastTile.y, 0.16f * 2, 0.16f * 2, m_texGroundTileMiddle));
			Add(m_groundTileArray[m_groundTileArray.size()]);
		}
	}
	else if (!Input::IsKeyPressed(RD_KEY_LEFT) && !Input::IsKeyPressed(RD_KEY_RIGHT))
	{
		m_marioSprite->SetTexture(m_texMarioBigStill);
	}

	if (Input::IsKeyPressed(RD_KEY_UP))
	{
		vec2 pos = m_marioSprite->GetPosition();
		pos.y += speed;
		m_marioSprite->SetPosition(pos);
	}
	else if (Input::IsKeyPressed(RD_KEY_DOWN))
	{
		vec2 pos = m_marioSprite->GetPosition();
		pos.y -= speed;
		m_marioSprite->SetPosition(pos);
	}*/
}

bool Test2D::OnKeyPressedEvent(KeyPressedEvent& event)
{
	if (!m_Renderer)
		return false;

	//Renderer2D& renderer = *m_Renderer;

	if (event.GetRepeat())
		return false;

	/*if (event.GetKeyCode() == RD_KEY_T)
	{
		renderer.SetRenderTarget(renderer.GetRenderTarget() == RenderTarget::SCREEN ? RenderTarget::BUFFER : RenderTarget::SCREEN);
		return true;
	}
	if (event.GetKeyCode() == RD_KEY_P)
	{
		renderer.SetPostEffects(!renderer.GetPostEffects());
		return true;
	}*/

	return false;
}

bool Test2D::OnMousePressedEvent(MousePressedEvent& event)
{
	return false;
}

void Test2D::OnEvent(radi::events::Event& event)
{
	EventDispatcher dispatcher(event);
	dispatcher.Dispatch<KeyPressedEvent>(METHOD(&Test2D::OnKeyPressedEvent));
	dispatcher.Dispatch<MousePressedEvent>(METHOD(&Test2D::OnMousePressedEvent));
}

void Test2D::OnRender(Renderer2D& renderer)
{
	debugInfo[0]->SetText(String("Target: ") + (renderer.GetRenderTarget() == RenderTarget::SCREEN ? "Screen" : "Buffer"));
	debugInfo[1]->SetText(String("PostFX: ") + (renderer.GetPostEffects() ? "On" : "Off"));
}