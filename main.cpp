#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

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
