#include <radi.h>

#include "TestLayer.h"
#include "Test3D.h"
#include "Sponza.h"
#include "../../Dependencies/GLEW/include/GL/glew.h"

using namespace radi;
using namespace graphics;
using namespace maths;

#define WIDTH	1280
#define HEIGHT	720

class Game : public Application
{
public:
	Game()
		: Application("Sandbox", WIDTH, HEIGHT, radi::graphics::API::RenderAPI::DIRECT3D)
	{
	}

	~Game()
	{
	}

	void Init() override
	{
		Application::Init();

		VFS::Get()->Mount("models", "res/models");
		VFS::Get()->Mount("pbr", "res/pbr");
		VFS::Get()->Mount("shaders", "shaders");

		//PushLayer(new Test3D());
		//PushLayer(new Test2D());
		PushLayer(new Sponza());
	}
};

int main()
{
	Game game;
	game.Start();
	return 0;
}