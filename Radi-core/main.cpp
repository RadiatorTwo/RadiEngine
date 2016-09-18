#include <GL/glew.h>
#include "src/utils/timer.h"

#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderer2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"

#include  "src/graphics/layers/layer.h"
#include  "src/graphics/layers/tilelayer.h"

#include "src/graphics/layers/group.h"

#include "src/graphics/texture.h"

#define BENCHMODE 0

int main()
{
	using namespace radi;
	using namespace graphics;
	using namespace maths;
	using namespace utils;

	Window window("Radi-Engine!", 960, 540);
	// glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader* s = new Shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	Shader& shader = *s;
	shader.enable();
	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));

	TileLayer layer(&shader);

	Texture* textures[] =
	{
		new Texture("test.png"),
		new Texture("test2.png"),
		new Texture("test3.png")
	};

#if BENCHMODE

	for (float y = -9.0f; y < 9.0f; y += 0.1f)
	{
		for (float x = -16.0f; x < 16.0f; x += 0.1f)
		{
			if (rand() % 4 == 0)
				layer.add(new Sprite(x, y, 0.09f, 0.09f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			else
				layer.add(new Sprite(x, y, 0.09f, 0.09f, textures[rand() % 3]));
		}
	}
#else

	for (float y = -9.0f; y < 9.0f; y++)
	{
		for (float x = -16.0f; x < 16.0f; x++)
		{
			if (rand() % 4 == 0)
				layer.add(new Sprite(x, y, 0.9f, 0.9f, maths::vec4(rand() % 1000 / 1000.0f, 0, 1, 1)));
			else
				layer.add(new Sprite(x, y, 0.9f, 0.9f, textures[rand() % 3]));
		}
	}

#endif

	GLint texIDs[] =
	{
		0,1,2,3,4,5,6,7,8,9
	};

	shader.enable();
	shader.setUniform1iv("textures", 10, texIDs);
	shader.setUniformMat4("pr_matrix", maths::mat4::orthographic(-16.0f, 16.0f, -9.0f, 9.0f, -1.0f, 1.0f));

	Timer time;
	float timer = 0;
	unsigned int frames = 0;
	while (!window.closed())
	{
		window.clear();
		double x, y;
		window.getMousePosition(x, y);
		shader.enable();
		shader.setUniform2f("light_pos", vec2((float)(x * 32.0f / 960.0f - 16.0f), (float)(9.0f - y * 18.0f / 540.0f)));

		layer.render();

		window.update();

		frames++;
		if (time.elapsed() - timer > 1.0f)
		{
			timer += 1.0f;
			printf("%d fps\n", frames);
			frames = 0;
		}
	}

	for (int i = 0; i < 3; i++)
	{
		delete textures[i];
	}

	return 0;
}