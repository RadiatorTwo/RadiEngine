#include <GL/glew.h>
#include <iostream>
#include "src/graphics/window.h"
#include "src/maths/maths.h"

int main()
{
	using namespace radi;
	using namespace graphics;
	using namespace maths;

	Window window("Radi!", 800, 600);

	glClearColor(0.2f, 0.3f, 0.8f, 1.0f);

	GLuint vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);

	vec4 a(1.0f, 2.0f, 5.0f, 4.0f);
	vec4 b(2, 4, 6, 4.0f);

	vec4 c = a + b;

	std::cout << a << std::endl;

	while (!window.closed())
	{
		window.clear();

		glBegin(GL_TRIANGLES);
		glVertex2f(0, 0.5);
		glVertex2f(-0.4, 0);
		glVertex2f(0.4, 0);
		glEnd();

		glDrawArrays(GL_ARRAY_BUFFER, 0, 6);

		window.update();
	}

	return 0;
}
