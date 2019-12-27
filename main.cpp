#include "Pyramidix.h"
#define TIMER_INTERVAL 10
#define TIMER_ID 0


static int window_width, window_height;
static int animation_ongoing;

int  posx=0;
int posy=0;
int topSmall = 0;
int topMiddle=0;
int bottomRight=0;
int fi=0;
int flag;

Pyramidix PX;


static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int);
static void on_display2(void);
void draw_axes(void);

using namespace std;


int main(int argc,char** argv){


  PX = Pyramidix();
  animation_ongoing = 0;
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
  glutDisplayFunc(on_display2);
  glutIdleFunc(on_display2);

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
		30,
		window_width / (float)window_height,
		1, 20);
}
/*Ne koristi se trenutno*/
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



  /*Translirati teziste srednje piramide na koordinanti pocetak*/
  glTranslatef(-1.5f, -sqrt(6)/4,  -sqrt(3) / 2);

  /*Rotacija cele piramide oko tezista*/
  glTranslatef(1.5f, sqrt(6) / 4,  sqrt(3) / 2);
  glRotatef(fi, 0.0f, 1.0f, 0.0f);
  glRotatef(posy, 1.0f, 0.0f, 0.0f);
	glTranslatef(-1.5f, -sqrt(6) / 4,  -sqrt(3) / 2);



  /*Pravljenje manjih piramida i iscrtavanje na scenu*/
	Pyramid A11 = Pyramid(Point(0.0f, 0.0f, 0.0f));//A11.Draw();
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

  /*Rotacija donje male piramide */
  glPushMatrix();
	glTranslatef(0.5f, sqrt(6) / 12, sqrt(3) / 6);
	glRotatef(bottomRight, 0.5f, sqrt(6) / 12, sqrt(3) / 6);
	glTranslatef(-0.5f, -sqrt(6) / 12, -sqrt(3) / 6);
	A11.Draw();
	glPopMatrix();


	glutSwapBuffers();

}


static void on_keyboard(unsigned char key, int x, int y)
{
  switch (key) {
	case 27:
		/* Zavrsava se program. */
		exit(0);
		break;
	case 'd':
		PX.RotationOnY += 10;
		break;
	case 'a':
		PX.RotationOnY -= 10;
		break;
	case 's':
		PX.RotationOnX -= 10;
		break;
	case 'q':
		PX.RotateTopBig(120);
		break;
	case 'Q':
		PX.RotateTopBig(-120);
		break;
	case 'w':
		PX.RotateBottomLeftBig(120);
		break;
	case 'W':
		PX.RotateBottomLeftBig(-120);
		break;
	case 'e':
		PX.RotateBottomRightBig(120);
		break;
	case 'E':
		PX.RotateBottomRightBig(-120);
		break;
	case 'r':
		PX.RotateBottomBehindBig(120);
		break;
	case 'R':
		PX.RotateBottomBehindBig(-120);
		break;
	case '1':
		PX.RotateTop(60);
		break;
	case '!':
		PX.RotateTop(-60);
		break;
	case '2':
		PX.RotateBottomLeft(60);
		break;
	case '@':
		PX.RotateBottomLeft(60);
		break;
	case '3':
		PX.RotateBottomRight(60);
		break;
	case '#':
		PX.RotateBottomRight(60);
		break;
	case '4':
		PX.RotateBottomBehind(60);
		break;
	case '$':
		PX.RotateBottomBehind(60);
		break;

	}
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



/*Pokusaj da se drugacije nacrta piramida*/
static void on_display2(void)
{
	/* Brise se prethodni sadrzaj prozora. */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(
		6, 6, -6,
		0, 0, 0,
		0, 1, 0
	);

	PX.Draw();
  draw_axes();

	glutSwapBuffers();
}
static void on_timer(int value)
{

    if (value != TIMER_ID)
      return;
    if(flag==1)
      fi+=10;
    else
      fi-=10;

    if(abs(fi)%90==0){
      animation_ongoing=0;
      return;
    }
    /* Forsira se ponovno iscrtavanje prozora. */
    glutPostRedisplay();

    /* Po potrebi se ponovo postavlja tajmer. */
    if (animation_ongoing) {
        glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
}
