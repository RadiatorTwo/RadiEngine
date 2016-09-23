# include "../src/radi.h"

using namespace radi;
using namespace graphics;

class Game : public Radi
{
private:
	Window* window;
	Layer* layer;
	Label* fps;
	Sprite* mario;
	Sprite* wall;
	Shader* shader;
public:
	Game()
	{

	}

	~Game()
	{
		delete layer;
	}

	void init() override
	{
		window = createWindow("Test Game", 960, 540);
		FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);
		shader = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
		layer = new Layer(new BatchRenderer2D(), shader, mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		mario = new Sprite(0.0f, 0.0f, 0.15 * 4, 0.20 * 4, new Texture("Mario", "mario.png"));
		wall = new Sprite(0.5f, 0.5f, 4, 4, new Texture("Wall", "test2.png"));
		layer->add(mario);
		layer->add(wall);

		fps = new Label("", -15.5f, 7.8f, 0xffffffff);
		layer->add(fps);
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

		maths::vec2 mouse = window->getMousePosition();
		shader->setUniform2f("light_pos", maths::vec2((float)(mouse.x * 32.0f / window->getWidth() - 16.0f), (float)(9.0f - mouse.y * 18.0f / window->getHeight())));
	}

	void render() override
	{
		layer->render();
	}

};

int main()
{
	Game game;
	game.start();
	return 0;
}