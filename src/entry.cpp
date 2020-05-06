#include <iostream>
#include <cstdio>
#include <GLFW/glfw3.h>
#include <gmpxx.h>
#include "config.h"
#include "data.h"
using namespace std;

int main()
{
	GLFWwindow *window;
	if (!glfwInit())
		return -1;
	window = glfwCreateWindow(
		config::pixelWidth << 1,
		config::pixelWidth << 1,
		"Mandelbrot Demo",
		nullptr, nullptr);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);
	data::init();
	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		//get the current width and height of the window,
		//in case the window is resized by the user
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		//Set up the viewport (using the width and height of the window)
		//and clear the screen color buffer.
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
		//Set up the camera matrix. Note: further details on the camera model will be discussed in Chapter 3
		glMatrixMode(GL_PROJECTION);
		glLoadIdentity();
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, 1.f);
		//void glOrtho(GLdouble left,GLdouble right,GLdouble bottom,GLdouble top,GLdouble near,GLdouble far);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		glBegin(GL_POINTS);
		data::point *p;
		for (int i = 0; i < config::pixelWidth; ++i)
		{
			for (int j = 0; j < config::pixelWidth; j++)
			{
				p = &data::points[i][j];
				float col = data::color(i, j);
				if (p->escaped == config::maxEscapeCount)
					glColor3f(1, 0.1f, 0.1f);
				else
					glColor3f(1 - col, 1 - col, col);
				glVertex2f(p->x, p->y);
			}
		}
		glEnd();
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glfwTerminate();
	return 0;
}
