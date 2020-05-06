#pragma once
#include <GLFW/glfw3.h>
#include <gmpxx.h>
#include "config.h"
namespace data
{
typedef struct
{
	GLfloat x, y;
	short escaped;
} point;
extern point points[][config::pixelWidth];
extern void init();
extern float color(short, short);
extern GLfloat xCenter,
	yCenter,
	ratio;
} // namespace data
