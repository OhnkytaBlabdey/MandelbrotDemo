#include <iostream>
#include <cstdio>
#include <GLFW/glfw3.h>
#include <gmpxx.h>
#include "config.h"
#include "data.h"
#include "key.h"
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
	// 启用阴影平滑
	glShadeModel(GL_SMOOTH);
	// 黑色背景
	// glClearColor(0.0, 0.0, 0.0, 0.0);
	// 设置深度缓存
	// glClearDepth(1.0);
	// 启用深度测试
	// glEnable(GL_DEPTH_TEST);
	// 所作深度测试的类型
	// glDepthFunc(GL_LEQUAL);
	// 告诉系统对透视进行修正
	// glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	data::init();
	glfwSetKeyCallback(window, key_callback);
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

		// glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		// glLoadIdentity(); // Reset The View
		// glTranslatef(0.0f, 0.0f, -2.0f);
		glBegin(GL_POINTS);
		glPointSize(2.0);
		data::point *p;
		for (int i = 0; i < config::pixelWidth; ++i)
		{
			for (int j = 0; j < config::pixelWidth; j++)
			{
				p = &data::points[i][j];
				float col = data::color(i, j);
				if (p->escaped == config::maxEscapeCount)
					glColor3f(0.1f, 0.1f, 0.1f);
				else
					glColor4f(
						(1 - col), (col - 0.5) * (col - 0.5) + 0.5, col,
						((float)p->escaped) / config::maxEscapeCount);
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
