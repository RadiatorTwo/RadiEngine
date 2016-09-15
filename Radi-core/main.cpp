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

	mat4 position = mat4::translation(vec3(2, 3, 4));
	position *= mat4::identity();

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
