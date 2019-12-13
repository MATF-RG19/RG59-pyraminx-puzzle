#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "Pyramid.h"

static int window_width, window_height;

static void on_reshape(int width, int height);
static void on_display(void);
void draw_axes(void);

int main(int argc,char** argv){

  /* inicijalizuje se GLUT*/
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DEPTH | GLUT_DOUBLE);

  /* kreira se prozor */
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);

  /* callback funkcije */
  glutReshapeFunc(on_reshape);
  glutDisplayFunc(on_display);
  glutIdleFunc(on_display);

  glClearColor(0.75, 0.75, 0.75, 0);
  glEnable(GL_DEPTH_TEST);

  glutMainLoop();

  return 0;

}

static void on_reshape(int width, int height)
{
	/*Pamti se sirina i visina*/
	window_width = width;
	window_height = height;

	glViewport(0, 0, window_width, window_height);

  /*Perspektiva*/
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(
		60,
		window_width / (float)window_height,
		1, 20);
}

static void on_display(void)
{

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  /*Polozaj kamere*/
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		6, 6, 6,
		0, 0, 0,
		0, 1, 0
	);
  draw_axes();

  /*Iscrtava se piramimda*/
  Pyramid A11 = Pyramid(Point(0.0f, 0.0f, 0.0f));
	Pyramid A12 = Pyramid(A11.PointDownRight);
	Pyramid A13 = Pyramid(A12.PointDownRight);
	Pyramid A21 = Pyramid(A11.PointDownMiddle);
	Pyramid A22 = Pyramid(A21.PointDownRight);
	Pyramid A31 = Pyramid(A21.PointDownMiddle);
	Pyramid B11 = Pyramid(A11.PointUp);
	Pyramid B12 = Pyramid(B11.PointDownRight);
	Pyramid B21 = Pyramid(B11.PointDownMiddle);
	Pyramid C11 = Pyramid(B11.PointUp);


  /*Iscrtavaju se trouglovi kako bi se dopunio ceo oblik piramide*/
  Triangle Front11, Front12, Front21, Left11, Left12, Left21, Right11, Right12, Right21, Bottom11, Bottom12, Bottom21;

  Front11 = Triangle(A11.PointDownRight, A11.PointUp, A12.PointUp, Green);
  Front12 = Triangle(A12.PointDownRight, A12.PointUp, A13.PointUp, Green);
  Front21 = Triangle(B11.PointDownRight, B11.PointUp, B12.PointUp,  Green);

  Left11 = Triangle(A11.PointDownMiddle, A11.PointUp, A21.PointUp, Blue);
  Left12 = Triangle(A21.PointDownMiddle, A21.PointUp, A31.PointUp, Blue);
  Left21 = Triangle(B11.PointDownMiddle, B11.PointUp, B21.PointUp, Blue);

  Right11 = Triangle(A13.PointDownMiddle, A13.PointUp, A22.PointUp, Yellow);
  Right12 = Triangle(A22.PointDownMiddle, A22.PointUp, A31.PointUp, Yellow);
  Right21 = Triangle(B12.PointDownMiddle, B12.PointUp, B21.PointUp, Yellow);

  Bottom11 = Triangle(A11.PointDownRight, A11.PointDownMiddle, A12.PointDownMiddle, Red);
  Bottom12 = Triangle(A12.PointDownRight, A12.PointDownMiddle, A13.PointDownMiddle, Red);
  Bottom21 = Triangle(A21.PointDownRight, A21.PointDownMiddle, A22.PointDownMiddle, Red);

	glutSwapBuffers();

}

void draw_axes(){
  /*Crvena x osa*/
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(1);
  glBegin(GL_LINES);
    glVertex3f(-4.0, 0.0f, 0.0f);
	  glVertex3f(4.0, 0.0f, 0.0f);
  glEnd();
	glFlush();

	/*Zelena y osa*/
	glColor3f(0.0, 1.0, 0.0);
	glBegin(GL_LINES);
	  glVertex3f(0.0, -4.0f, 0.0f);
	  glVertex3f(0.0, 4.0f, 0.0f);
	glEnd();
	glFlush();

	/*Plava z osa*/
	glColor3f(0.0, 0.0, 1.0); // blue z
	glBegin(GL_LINES);
	  glVertex3f(0.0, 0.0f, -4.0f);
	  glVertex3f(0.0, 0.0f, 4.0f);

	glEnd();
	glFlush();

}
