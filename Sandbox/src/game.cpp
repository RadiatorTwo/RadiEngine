# include "../src/radi.h"

#define GAME_MODE 0

using namespace radi;
using namespace graphics;

class Game : public Radi
{
private:
#if GAME_MODE
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
	maths::vec3 mask;
#else
	Window* window;
	Layer* layer;
	Label* fps;
	Sprite* sprite;
	Shader* shader;
	maths::vec3 mask;
#endif
public:
	Game()
	{
	}

	~Game()
	{
#if GAME_MODE
		delete layer1;
		delete layer2;
		delete layer3;
#else
		delete layer;
#endif
	}

#if GAME_MODE
	void init() override
	{
		window = createWindow("Test Game", 960, 540);
		FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);

		shader1 = ShaderFactory::DefaultShader();
		shader2 = ShaderFactory::DefaultShader();
		shader3 = ShaderFactory::DefaultShader();
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

		Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
		layer1->setMask(new Texture("Mask", "res/mask.png"));
		layer2->setMask(new Texture("Mask", "res/mask.png"));
		layer3->setMask(new Texture("Mask", "res/mask.png"));

		shader1->enable();
		shader2->enable();
		shader3->enable();
		shader1->setUniformMat4("mask_matrix", maths::mat4::translation(mask));
		shader2->setUniformMat4("mask_matrix", maths::mat4::translation(mask));
		shader3->setUniformMat4("mask_matrix", maths::mat4::translation(mask));
	}
#else
	void init() override
	{
		window = createWindow("Test Game", 960, 540);
		FontManager::get()->setScale(window->getWidth() / 32.0f, window->getHeight() / 18.0f);

		shader = ShaderFactory::DefaultShader();

		layer = new Layer(new BatchRenderer2D(), shader, maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));
		sprite = new Sprite(0.0f, 0.0f, 4, 4, new Texture("Tex", "res/mario.png"));
		layer->add(new Sprite(-16.0f, -9.0f, 32, 32, 0xffff00ff));
		layer->add(sprite);

		fps = new Label("", -15.5f, 7.8f, 0xffffffff);
		layer->add(fps);

		Texture::SetWrap(TextureWrap::CLAMP_TO_BORDER);
		layer->setMask(new Texture("Mask", "res/mask.png"));

		shader->enable();
		shader->setUniformMat4("mask_matrix", maths::mat4::translation(mask));

		//		audio::SoundManager::add(new audio::Sound("Lol", "res/Cherno.ogg"))->loop();
	}
#endif

	void tick() override
	{
		fps->text = std::to_string(getFPS()) + " fps";
		RADI_INFO(getUPS(), " ups, ", getFPS(), " fps");
	}

#if GAME_MODE
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

#else
	void update() override
	{
		float speed = 0.01f;
		if (window->isKeyPressed(GLFW_KEY_UP))
			sprite->position.y += speed;
		else if (window->isKeyPressed(GLFW_KEY_DOWN))
			sprite->position.y -= speed;
		if (window->isKeyPressed(GLFW_KEY_LEFT))
			sprite->position.x -= speed;
		else if (window->isKeyPressed(GLFW_KEY_RIGHT))
			sprite->position.x += speed;

		if (window->isKeyPressed(GLFW_KEY_UP))
			mask.y += speed;
		else if (window->isKeyPressed(GLFW_KEY_DOWN))
			mask.y -= speed;
		if (window->isKeyPressed(GLFW_KEY_LEFT))
			mask.x -= speed;
		else if (window->isKeyPressed(GLFW_KEY_RIGHT))
			mask.x += speed;

		static maths::vec3 scale(1, 1, 1);
		if (window->isKeyPressed(GLFW_KEY_W))
		{
			scale.x += speed;
			scale.y += speed;
		}
		else if (window->isKeyPressed(GLFW_KEY_S))
		{
			scale.x -= speed;
			scale.y -= speed;
		}

		maths::vec2 mouse = window->getMousePosition();
		shader->setUniformMat4("mask_matrix", maths::mat4::translation(mask) * maths::mat4::scale(scale));
		// shader->setUniform2f("light_pos", maths::vec2((float)(mouse.x * 32.0f / window->getWidth() - 16.0f), (float)(9.0f - mouse.y * 18.0f / window->getHeight())));
	}

	void render() override
	{
		layer->render();
	}
#endif

};

int main()
{
	Game game;
	game.start();
	return 0;
}