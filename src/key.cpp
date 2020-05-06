#include "key.h"
#include "data.h"

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	if (action != GLFW_PRESS)
		return;
	int rate = 16;
	switch (key)
	{
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GL_TRUE);
		break;
	case GLFW_KEY_A:
		data::xCenter -= data::ratio / rate;
		break;
	case GLFW_KEY_D:
		data::xCenter += data::ratio / rate;
		break;
	case GLFW_KEY_S:
		data::yCenter -= data::ratio / rate;
		break;
	case GLFW_KEY_W:
		data::yCenter += data::ratio / rate;
		break;
	case GLFW_KEY_UP:
		data::ratio *= 0.75;
		break;
	case GLFW_KEY_DOWN:
		data::ratio *= 1.33;
		break;
	default:
		return;
	}
	printf("updating ...\n");
	data::init();
}