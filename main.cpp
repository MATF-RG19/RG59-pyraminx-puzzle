#include "Pyramidix.h"

#define TIMER_INTERVAL 50
#define TIMER_ID 0


static int window_width, window_height;
static int animation_ongoing;

//oznaka pravca rotacije, l za levo, r - za desno
char directionFlag = 'l';
//Simbol rotacije koji obelezava koja strana se rotira, t -top, l - left, r - right, b-behind
char rotationFlag = 't';
//Flag male ili velike rotacije s - mala, l - velika
char sizeFlag = 's';


int curentTick = 0;
int MaxTick = 9;

Pyramidix PX;


static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int);
static void rotate(int degree);


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
    if (!animation_ongoing) {
      directionFlag = 'r';
			sizeFlag = 'l';
			rotationFlag ='t';
      animation_ongoing = 1;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'Q':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 'l';
      rotationFlag = 't';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'w':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 'l';
      rotationFlag = 'l';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'W':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 'l';
      rotationFlag = 'l';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'e':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 'l';
      rotationFlag = 'r';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'E':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 'l';
      rotationFlag = 'r';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'r':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 'l';
      rotationFlag = 'b';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'R':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 'l';
      rotationFlag = 'b';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '1':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 's';
      rotationFlag = 't';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '!':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 's';
      rotationFlag = 't';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '2':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 's';
      rotationFlag = 'l';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '@':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 's';
      rotationFlag = 'l';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '3':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 's';
      rotationFlag = 'r';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '#':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 's';
      rotationFlag = 'r';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '4':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 's';
      rotationFlag = 'b';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '$':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 's';
      rotationFlag = 'b';
      animation_ongoing = 1;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
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


static void rotate(int degree)
{
	if (sizeFlag == 's')
	{
		switch (rotationFlag)
		{
			case 't' : PX.RotateTop(degree);
				break;
			case 'l': PX.RotateBottomLeft(degree);
				break;
			case 'r': PX.RotateBottomRight(degree);
				break;
			case 'b': PX.RotateBottomBehind(degree);
				break;
		}
	}
	else
	{
		switch (rotationFlag)
		{
		case 't': PX.RotateTopBig(degree);
			break;
		case 'l': PX.RotateBottomLeftBig(degree);
			break;
		case 'r': PX.RotateBottomRightBig(degree);
			break;
		case 'b': PX.RotateBottomBehindBig(degree);
			break;
		}
	}
}





static void on_timer(int value)
{
  if (value != TIMER_ID)
    return;

  if (directionFlag == 'l')
		rotate(12);
  else
    rotate(-12);

  curentTick++;
  if (curentTick > MaxTick) {
    animation_ongoing = 0;
    curentTick = 0;
    return;
  }


  /* Forsira se ponovno iscrtavanje prozora. */
  glutPostRedisplay();

  /* Po potrebi se ponovo postavlja tajmer. */
  if (animation_ongoing) {
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
  }
}
