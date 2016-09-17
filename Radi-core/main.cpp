#include <GL/glew.h>
#include <iostream>
#include "src/graphics/window.h"
#include "src/graphics/shader.h"
#include "src/maths/maths.h"

#include "src/graphics/buffers/buffer.h"
#include "src/graphics/buffers/indexbuffer.h"
#include "src/graphics/buffers/vertexarray.h"

#include "src/graphics/renderable2d.h"
#include "src/graphics/simple2drenderer.h"
#include "src/graphics/batchrenderer2d.h"

#include "src/graphics/static_sprite.h"
#include "src/graphics/sprite.h"

#define BATCH_RENDERER 1

int main()
{
	using namespace radi;
	using namespace graphics;
	using namespace maths;

	Window window("Radi!", 800, 600);

	//glClearColor(0.5f, 0.5f, 0.5f, 1.0f);


	GLfloat vertices[] =
	{
		0, 0, 0,
		0, 3, 0,
		8, 3, 0,
		8, 0, 0,
	};

	GLushort indices[] =
	{
		0, 1, 2,
		2, 3, 0
	};

	GLfloat colorsA[] =
	{
		1,0,1,1,
		1,0,1,1,
		1,0,1,1,
		1,0,1,1
	};

	GLfloat colorsB[] =
	{
		0.2f,0.3f,0.8f,1,
		0.2f,0.3f,0.8f,1,
		0.2f,0.3f,0.8f,1,
		0.2f,0.3f,0.8f,1
	};

	mat4 ortho = mat4::orthographic(0.0f, 16.0f, 0.0f, 9.0f, -1.0f, 1.0f);

	Shader shader("src/shaders/basic.vert", "src/shaders/basic.frag");
	shader.enable();

	shader.setUniformMat4("pr_matrix", ortho);
	//shader.setUniformMat4("ml_matrix", mat4::translation(vec3(4, 3, 0)));
#if BATCH_RENDERER
	Sprite sprite1(5, 5, 4, 4, maths::vec4(1, 0, 1, 1));
	Sprite sprite2(7, 1, 2, 3, maths::vec4(0.2f, 0, 1, 1));
	
	BatchRenderer2D renderer;
#else
	StaticSprite sprite1(5, 5, 4, 4, maths::vec4(1, 0, 1, 1), shader);
	StaticSprite sprite2(7, 1, 2, 3, maths::vec4(0.2f, 0, 1, 1), shader);
	Simple2DRenderer renderer;
#endif

	shader.setUniform2f("light_pos", vec2(4.0f, 1.5f));
	shader.setUniform4f("colour", vec4(0.2f, 0.3f, 0.8f, 1.0f));

	while (!window.closed())
	{
		window.clear();

		double x, y;
		window.getMousePosition(x, y);

		shader.setUniform2f("light_pos", vec2((float)(x * 16.0f / 800.0f), (float)(9.0f - y * 9.0f / 600.0f)));

#if BATCH_RENDERER
		renderer.begin();
#endif
		renderer.submit(&sprite1);
		renderer.submit(&sprite2);

#if BATCH_RENDERER
		renderer.end();
#endif
		renderer.flush();
		
		window.update();
	}

	return 0;
}
