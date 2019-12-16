#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>
#include "Pyramid.h"

static int window_width, window_height;


int  posx=0;
int posy=0;
int topSmall = 0;
int topMiddle=0;

static void on_keyboard(unsigned char key, int x, int y);
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
  glutKeyboardFunc(on_keyboard);
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
		6, 6, -6,
		0, 0, 0,
		0, 1, 0
	);
  draw_axes();


  /*Translirati teziste srednje piramide na koordinanti pocetak*/
	glTranslatef(-1.5f, -sqrt(6)/4,  -sqrt(3) / 2);

  /*Rotacija cele piramide oko tezista*/
	glTranslatef(1.5f, sqrt(6) / 4,  sqrt(3) / 2);
	glRotatef(posx, 0.0f, 1.0f, 0.0f);
	glRotatef(posy, 1.0f, 0.0f, 0.0f);
	glTranslatef(-1.5f, -sqrt(6) / 4,  -sqrt(3) / 2);



  /*Pravljenje manjih piramida i iscrtavanje na scenu*/
	Pyramid A11 = Pyramid(Point(0.0f, 0.0f, 0.0f));A11.Draw();
	Pyramid A12 = Pyramid(A11.PointDownRight); A12.Draw();
  Pyramid A13 = Pyramid(A12.PointDownRight);A13.Draw();
	Pyramid A21 = Pyramid(A11.PointDownMiddle); A21.Draw();
	Pyramid A22 = Pyramid(A21.PointDownRight); A22.Draw();
	Pyramid A31 = Pyramid(A21.PointDownMiddle);A31.Draw();


	Pyramid B11 = Pyramid(A11.PointUp);
	Pyramid B12 = Pyramid(B11.PointDownRight);
  Pyramid B21 = Pyramid(B11.PointDownMiddle);

	Pyramid C11 = Pyramid(B11.PointUp);

  /*Pravljenje trouglova*/
  Triangle Front11, Front12, Front21, Left11, Left12, Left21, Right11, Right12, Right21, Bottom11, Bottom12, Bottom21;
	Front11 = Triangle(A11.PointDownRight, A11.PointUp, A12.PointUp, Green);
	Front12 = Triangle(A12.PointDownRight, A12.PointUp, A13.PointUp, Green);
	Front21 = Triangle(B11.PointDownRight, B11.PointUp, B12.PointUp, Green);

	Left11 = Triangle(A11.PointDownMiddle, A11.PointUp, A21.PointUp, Blue);
	Left12 = Triangle(A21.PointDownMiddle, A21.PointUp, A31.PointUp, Blue);
	Left21 = Triangle(B11.PointDownMiddle, B11.PointUp, B21.PointUp, Blue);

	Right11 = Triangle(A13.PointDownMiddle, A13.PointUp, A22.PointUp, Yellow);
	Right12 = Triangle(A22.PointDownMiddle, A22.PointUp, A31.PointUp, Yellow);
	Right21 = Triangle(B12.PointDownMiddle, B12.PointUp, B21.PointUp, Yellow);

	Bottom11 = Triangle(A11.PointDownRight, A11.PointDownMiddle, A12.PointDownMiddle, Red);
	Bottom12 = Triangle(A12.PointDownRight, A12.PointDownMiddle, A13.PointDownMiddle, Red);
	Bottom21 = Triangle(A21.PointDownRight, A21.PointDownMiddle, A22.PointDownMiddle, Red);


  /*Iscrtavanje trouglova na scenu da bi se dopunila piramida*/
	Front11.Draw();
	Front12.Draw();
  //Front21.Draw();
	Left11.Draw();
	Left12.Draw();
  //Left21.Draw();
	Right11.Draw();
	Right12.Draw();
  //Right21.Draw();
	Bottom11.Draw();
	Bottom12.Draw();
	Bottom21.Draw();

  /*Rotacija srednje piramide*/
  glPushMatrix();
  glTranslatef(1.5f, 0.0f, sqrt(3) / 2);
  glRotatef(topMiddle, 0.0f, 1.0f, 0.0f);
  glTranslatef(-1.5f, 0.0f, -sqrt(3) / 2);
  B11.Draw();
  B12.Draw();
  B21.Draw();

  Front21.Draw();
  Left21.Draw();
  Right21.Draw();

  /*Rotacija male piramide na vrhu*/
  glPushMatrix();
  glTranslatef(1.5f, 0.0f, sqrt(3) / 2);
  glRotatef(topSmall, 0.0f, 1.0f, 0.0f);
  glTranslatef(-1.5f, 0.0f, -sqrt(3) / 2);
  C11.Draw();
  glPopMatrix();

  glPopMatrix();

	glutSwapBuffers();

}


static void on_keyboard(unsigned char key, int x, int y)
{
	switch (key) {
	case 27:
		exit(0);
		break;
	case 'd':
    posx+=10;
    break;
	case 'a':
    posx -= 10;
		break;
	case 'w':
    posy -= 10;
		break;
	case 's':
    posy += 10;
		break;
  case '1':
  	topSmall += 60;
  	break;
  case '3':
  	topSmall -=60;
  	break;
  case 'q':
    topMiddle += 60;
    break;
  case 'e':
    topMiddle -= 60;
    break;
	}
	if (abs(posx) >= 360)
		posx = 0;
	if (abs(posy) >= 360)
		posy = 0;


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
