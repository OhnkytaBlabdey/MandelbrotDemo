#include <iostream>
#include <cstdio>
#include <GLFW/glfw3.h>
#include <gmpxx.h>
using namespace std;

int main()
{
	mpf_class S;
	mpf_class a, b;
	S = 0;
	a = 1;
	b = 1.0;
	int n = 200;
	while (n--)
	{
		S += b / a;
		a += 1;
	}
	printf("%.6lf", S.get_d());

	GLFWwindow *window;
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(480, 320, "TestOpenGL", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	while (!glfwWindowShouldClose(window))
	{
		glBegin(GL_TRIANGLES);

		glColor3f(1.0, 0.0, 0.0);
		glVertex3f(0.0, 1.0, 0.0);
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f(-1.0, -1.0, 0.0);
		glColor3f(1.0, 0.0, 1.0);
		glVertex3f(1.0, -1.0, 0.0);

		glEnd();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
