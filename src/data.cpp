#include "data.h"
namespace data
{
point points[config::pixelWidth][config::pixelWidth];
GLfloat xCenter = 0.f,
		yCenter = 0.f,
		ratio = 2.f;
inline short escape(mpf_class x, mpf_class y, short time)
{
	mpf_class z_x = 0, z_y = 0;
	mpf_class t_x, t_y;
	for (short i = 0; i < time; i++)
	{
		t_x = z_x * z_x - z_y * z_y + x;
		t_y = z_y * z_x * 2 + y;
		z_x = t_x;
		z_y = t_y;
		if ((z_x * z_x + z_y * z_y - 4) > 0)
		{
			return i;
		}
	}

	return time;
}
inline void validate(short i, short j)
{
	float x, y;
	// in screen
	x = points[i][j].x = ((float)i / config::pixelWidth) * 2 - 1;
	y = points[i][j].y = ((float)j / config::pixelWidth) * 2 - 1;
	// in real
	mpf_class X = xCenter + x * ratio,
			  Y = yCenter + y * ratio;
	points[i][j].escaped = escape(X, Y, config::maxEscapeCount);
	if ((i == 0 || (config::pixelWidth % i == 0 && (config::pixelWidth / i) % 32 == 0)) && (j == 0 || (config::pixelWidth % j == 0 && (config::pixelWidth / j) % 32 == 0)))
	{
		printf("(%d %d) (%f, %f) - (%lf, %lf):%d\n", i, j, x, y, X.get_d(), Y.get_d(), points[i][j].escaped);
	}
}
void init()
{
	for (short i = 0; i < config::pixelWidth; i++)
	{
		for (short j = 0; j < config::pixelWidth; j++)
		{
			validate(i, j);
		}
	}
}
float color(short i, short j)
{
	float r = (points[i][j].escaped % config::colorAmount) * (1.f / config::colorAmount);
	// printf("%d %d :%f\n", i, j, r);
	return r;
}
} // namespace data
