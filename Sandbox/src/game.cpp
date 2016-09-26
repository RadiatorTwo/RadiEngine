#include <radi.h>
#include <app/application.h>

#include "TestLayer.h"

using namespace radi;
using namespace graphics;
using namespace maths;

#define WIDTH 1280
#define HEIGHT 1024

class Game : public Application
{
public:
	Game()
		: Application("Test Game", WIDTH, HEIGHT)
	{
	}

	~Game()
	{
	}

	void Init() override
	{
		Application::Init();
		PushLayer(new TestLayer());
	}
};

int main()
{
	Game game;
	game.Start();
	return 0;
}