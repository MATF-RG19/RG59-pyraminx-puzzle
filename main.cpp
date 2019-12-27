#include "Pyramidix.h"

#define TIMER_INTERVAL 10
#define TIMER_ID 0


static int window_width, window_height;
static int animation_ongoing;

int fi=0;
int flag;

Pyramidix PX;


static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int);

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
		30,
		window_width / (float)window_height,
		1, 20);
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


static void on_display(void)
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

	glutSwapBuffers();
}

/*Trenutno se ne koristi*/
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
