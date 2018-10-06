
#include <glfw/glfw3.h>
//Include the GLFW library for creating windows with OpenGL contexts and managing user inputs

//#define modified
//extern int** mat;
//extern int init();
//const unsigned int m=256;
#include <stdio.h>
#include <gmp.h>


extern "C" {
	const unsigned int m = 256;
	const int n = 200;

	int mat[m + 1][m + 1];


	mpf_t x_, y_, T, S;
	// mpf_inits(x_,y_,T,S);
	short escape(mpf_t X, mpf_t Y, int N)
	{
		// mpf_t x_,y_,T,S;
		// mpf_inits(x_,y_,T,S);

		mpf_set_ui(x_, 0);
		mpf_set_ui(y_, 0);

		for (int i = 0; i < N; i++) {

			/*
			z' = z^2+c
			(x'+y'i) = (x + yi)(x + yi) + X + Yi
					 = (x*x - y*y + X) + (2*x*y + Y)i
			*/
			mpf_set_ui(S, 0);

			mpf_mul(T, x_, x_);
			mpf_add(S, S, T);

			mpf_mul(T, y_, y_);
			mpf_neg(T, T);
			mpf_add(S, S, T);

			mpf_add(S, S, X);
			mpf_set(T, x_);
			mpf_set(x_, S);

			mpf_mul(S, T, y_);
			mpf_mul_ui(S, S, 2);

			mpf_add(y_, S, Y);

			/*
			if |Z| > 2 then escape
			*/
			mpf_set_ui(S, 0);
			mpf_mul(T, x_, x_);
			mpf_add(S, S, T);
			mpf_mul(T, y_, y_);
			mpf_add(S, S, T);
			if (mpf_cmp_ui(S, 4) > 0)
				return i - 1;
			// else
				// gmp_printf("%.Ff\t%.Ff\n",x_,y_);
		}

		// mpf_clears(x_,y_,T,S);
		return N;
	}


	int init()
	{
		// mpf_inits(x_,y_,T,S);
		mpf_init(x_);
		mpf_init(y_);
		mpf_init(T);
		mpf_init(S);
		mpf_t x, y, dex, t, s;
		mpf_init(x);
		mpf_init(y);
		mpf_init(dex);
		mpf_init(t);
		mpf_init(s);

		// mpf_set_ui(t,m); // 最近的可表示数
		mpf_set_ui(x, 1);
		mpf_set_ui(y, 1);
		mpf_set_ui(dex, m / 2);
		mpf_ui_div(dex, 1, dex);


		for (int i = 0; i <= m; i++) {
			mpf_set_ui(x, 1);
			for (int j = 0; j <= m; j++) {
				mpf_set_ui(s, 0);
				mpf_mul(t, x, x);
				mpf_add(s, s, t);
				mpf_mul(t, y, y);
				mpf_add(s, s, t);

				// bool flag= (mpf_cmp_ui(s,1)>0);
				int flag = escape(x, y, n);
				mat[i][j] = flag;
				// if(!flag)
				// gmp_printf("%.Ff\t%.Ff\t%s\t%d\t%d\n",y,x,flag>0?"Yes":"No",j+1,i+1);
				mpf_sub(x, x, dex);
			}
			mpf_sub(y, y, dex);
		}

		mpf_clear(dex);
		mpf_clear(x);
		mpf_clear(t);
		mpf_clear(y);
		mpf_clear(s);

		// mpf_clears(x_,y_,T,S);
		mpf_clear(x_);
		mpf_clear(y_);
		mpf_clear(T);
		mpf_clear(S);
		/*for (int i = 0; i <= m; i++) {
			for (int j = 0; j <= m; j++) {
				printf("%03d ", mat[i][j]);
			}
			printf("\n");
		}*/

		return 0;
	}
}

void func(mpf_t res, mpf_t x)
{
	int prec;
	prec = mpf_get_prec(x);
	if (prec < 2556)
		prec = 256;
	mpf_t t;
	mpf_init2(t, prec);

	if (prec < int(mpf_get_prec(res))) prec = mpf_get_prec(res);
	mpf_set_prec(res, prec);

	mpf_set(t, x);
	mpf_set_ui(res, 0);

	mpf_mul(t, x, x);
	mpf_mul_ui(t, t, 2);
	mpf_add(res, res, t);

	mpf_add(res, res, x);
	mpf_sub_ui(res, res, 1);
	mpf_clear(t);
}

int main()
{
	//Initialize GLFW and create a GLFW window object (640 x 480).
	if (!glfwInit())
		exit(EXIT_FAILURE);

	GLFWwindow* window;
	window = glfwCreateWindow(640, 480, "Simple GLFW Example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(EXIT_FAILURE);
	}

	//make sure that the context of the specified window is current on the calling thread
	glfwMakeContextCurrent(window);
	GLfloat arr[m+1][m+1];
	init();
	for (int i = 0; i <= m; i++) {
		for (int j = 0; j <= m; j++) {
			arr[i][j] = (float)mat[i][j] / n;
		}
	}

	//Define a loop which terminates when the window is closed.
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
		glOrtho(-ratio, ratio, -1.f, 1.f, 1.f, -1.f);
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		
		//draw axis
		glLineWidth(1.5f);
		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex3f(-1.0f, 0, 0);
		glColor3f(1, 1, 1);
		glVertex3f(1.0f, 0, 0);
		glEnd();

		glBegin(GL_LINES);
		glColor3f(1, 1, 1);
		glVertex3f(0, -1.0f, 0);
		glColor3f(1, 1, 1);
		glVertex3f(0, 1.0f, 0);
		glEnd();
		//
		GLfloat x,y;
		glLineWidth(3.0f);
		//glBegin(GL_LINE);
		glBegin(GL_POINTS);
		for (int i = 0; i <= m; ++i) {
			for (int j = 0; j <= m; j++) {
				x = 1.0 - (2.0*i / m);
				y = 1.0 - (2.0*j / m);
				glColor3f(arr[i][j], 1 - arr[i][j], 1 - arr[i][j]);
			glVertex3f(y, x, 0);
		}
		}
			
		glEnd();


		//Swap the draw buffer
		glfwSwapBuffers(window);

		//for handling events such as keyboard input
		glfwPollEvents();
	}

	//Release the memory and terminate the GLFW library. Then, exit the application.
	glfwDestroyWindow(window);
	glfwTerminate();
	exit(EXIT_SUCCESS);
}
