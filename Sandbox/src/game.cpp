#include <radi.h>

#include "TestLayer.h"
#include "Test3D.h"
#include "Sponza.h"

using namespace radi;
using namespace graphics;
using namespace maths;

class Game : public Application
{
public:
	Game()
		: Application("Sandbox", { 3440, 1440, false, false }, API::RenderAPI::OPENGL)
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