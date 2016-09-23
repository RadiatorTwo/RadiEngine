# include "../src/radi.h"

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
		window = createWindow("Test Game", 960, 540);
		FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);
		shader1 = new Shader("shaders/basic.vert", "shaders/basic.frag");
		shader2 = new Shader("shaders/basic.vert", "shaders/basic.frag");
		shader3 = new Shader("shaders/basic.vert", "shaders/basic.frag");
		layer1 = new Layer(new BatchRenderer2D(), shader1, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layer2 = new Layer(new BatchRenderer2D(), shader2, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		layer3 = new Layer(new BatchRenderer2D(), shader3, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		

		for (float i = -16.0f; i < 16.0f; i += (5.12f * 4))
		{
			layer1->add(new Sprite(i, -9.0f, 5.12f * 4, 4.32f * 4, new Texture("ground", "res/background.png")));
		}

		for (float i = -16.0f; i < 16.0f; i += (0.16f * 4))
		{
			layer2->add(new Sprite(i, -9.0f, 0.16f * 4, 0.16f * 4, new Texture("ground", "res/ground_tile.png")));
		}

		fps = new Label("", -15.5f, 7.8f, 0xffffffff);
		layer3->add(fps);

		mario = new Sprite(0.0f, 0.0f, 0.15 * 4, 0.20 * 4, new Texture("Mario", "res/mario.png"));
		layer3->add(mario);
	}

	void tick() override
	{
		fps->text = std::to_string(getFPS());
		RADI_INFO(getUPS(), " ups, ", getFPS(), " fps");
		//std::cout << getUPS() << " ups " << getFPS() << " fps" << std::endl;
	}

	void update() override
	{
		float speed = 0.25f;
		if (window->isKeyPressed(GLFW_KEY_UP))
			mario->position.y += speed;
		if (window->isKeyPressed(GLFW_KEY_DOWN))
			mario->position.y -= speed;
		if (window->isKeyPressed(GLFW_KEY_LEFT))
			mario->position.x -= speed;
		if (window->isKeyPressed(GLFW_KEY_RIGHT))
			mario->position.x += speed;

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