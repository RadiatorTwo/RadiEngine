#include <radi.h>

#include "TestLayer.h"
#include "Test3D.h"

using namespace radi;
using namespace graphics;
using namespace maths;

#define WIDTH 1280
#define HEIGHT 720

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
		//PushLayer(new TestLayer());
		PushLayer(new Test3D());
	}
};

int main()
{
	Game game;
	game.Start();
	return 0;
}