# include "../src/radi.h"

#define GAME_MODE 0

using namespace radi;
using namespace graphics;

class Game : public Radi
{
private:

	Window* window;
	Layer* layer1;
	Layer* layer2;
	Layer* layer3;
	Label* fps;
	Sprite* mario;
	Sprite* ground;
	Shader* shader1;
	Shader* shader2;
	Shader* shader3;
	Label* debugInfo;

public:
	Game()
	{
	}

	~Game()
	{

		delete layer1;
		delete layer2;
		delete layer3;

	}


	void init() override
	{
		window = createWindow("Test Game", 1280, 720);
		FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);

		shader1 = ShaderFactory::DefaultShader();
		shader2 = ShaderFactory::DefaultShader();
		shader3 = ShaderFactory::DefaultShader();
		layer1 = new Layer(new BatchRenderer2D(maths::tvec2<uint>(1280, 720)), shader1, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layer2 = new Layer(new BatchRenderer2D(maths::tvec2<uint>(1280, 720)), shader2, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layer3 = new Layer(new BatchRenderer2D(maths::tvec2<uint>(1280, 720)), shader3, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

		for (float i = -16.0f; i < 16.0f; i += (5.12f * 4))
		{
			layer1->add(new Sprite(i, -9.0f + (0.16f * 4), 5.12f * 4, (9.0f * 2) - (0.16f * 4), new Texture("ground", "res/background.png")));
		}

		for (float i = -16.0f; i < 16.0f; i += (0.16f * 4))
		{
			layer2->add(new Sprite(i, -9.0f, 0.16f * 4, 0.16f * 4, new Texture("ground", "res/ground_tile.png")));
		}

		fps = new Label("", -15.5f, 7.8f, 0xff000000);
		layer3->add(fps);

		debugInfo = new Label("", -15.5f, 6.8f, 0xffffffff);
		layer3->add(debugInfo);

		mario = new Sprite(0.0f, 0.0f, 0.15 * 4, 0.20 * 4, new Texture("Mario", "res/mario.png"));
		layer3->add(mario);
        Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
	}

	void tick() override
	{
		fps->text = std::to_string(getFPS()) + " fps";
		RADI_INFO(getUPS(), " ups, ", getFPS(), " fps");
	}

	void update() override
	{
		if (window->isKeyPressed(GLFW_KEY_1))
		{
			((BatchRenderer2D*)layer1->renderer)->SetRenderTarget(RenderTarget::SCREEN);
			((BatchRenderer2D*)layer2->renderer)->SetRenderTarget(RenderTarget::SCREEN);
			((BatchRenderer2D*)layer3->renderer)->SetRenderTarget(RenderTarget::SCREEN);
		}

		if (window->isKeyPressed(GLFW_KEY_2))
		{
			((BatchRenderer2D*)layer1->renderer)->SetRenderTarget(RenderTarget::BUFFER);
			((BatchRenderer2D*)layer2->renderer)->SetRenderTarget(RenderTarget::BUFFER);
			((BatchRenderer2D*)layer3->renderer)->SetRenderTarget(RenderTarget::BUFFER);
		}

		maths::tvec2<uint> size1 = ((BatchRenderer2D*)layer1->renderer)->GetViewportSize();
		maths::tvec2<uint> size2 = ((BatchRenderer2D*)layer2->renderer)->GetViewportSize();
		maths::tvec2<uint> size3 = ((BatchRenderer2D*)layer3->renderer)->GetViewportSize();

		if (window->isKeyPressed(GLFW_KEY_UP))
		{
			size1.x++;
			size1.y++;
			size2.x++;
			size2.y++;
			size3.x++;
			size3.y++;
		}
		else if (window->isKeyPressed(GLFW_KEY_DOWN))
		{
			size1.x--;
			size1.y--;
			size2.x--;
			size2.y--;
			size3.x--;
			size3.y--;
		}

		debugInfo->text = std::to_string(size1.x) + ", " + std::to_string(size1.y);
		((BatchRenderer2D*)layer1->renderer)->SetViewportSize(size1);
		((BatchRenderer2D*)layer2->renderer)->SetViewportSize(size2);
		((BatchRenderer2D*)layer3->renderer)->SetViewportSize(size3);

		//maths::vec2 mouse = window->getMousePosition();
		//shader2->setUniform2f("light_pos", maths::vec2((float)(mouse.x * 32.0f / window->getWidth() - 16.0f), (float)(9.0f - mouse.y * 18.0f / window->getHeight())));
	}

	void render() override
	{
		layer1->render();
		layer2->render();
		layer3->render();
	}
};

int main()
{
	Game game;
	game.start();
	return 0;
}