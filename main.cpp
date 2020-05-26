#include "Pyramidix.h"
#include "texture/image.h"
#include <time.h>
#include<string>

#define TIMER_INTERVAL 50
#define TIMER_ID 0
#define START_TIMER_ID 1
#define START_TIMER_INT 60

/* Ime fajla sa teksturom*/
#define FILENAME0 "texture/background.bmp"
#define FILENAME1 "texture/startdisplay.bmp"

/* Identifikatori tekstura. */
static GLuint texture[2];


static int window_width, window_height;
static int animation_ongoing;

/*mis*/
static int mouse_x, mouse_y;
static void on_mouse(int button, int state, int x, int y);
static void on_motion(int x, int y);
/*matrica rotacije koja se azurira na pomeraj misa*/
static float matrix[16];

/*oznaka pravca rotacije, l za levo, r - za desno*/
char directionFlag = 'l';
/*Simbol rotacije koji obelezava koja strana se rotira, t -top, l - left, r - right, b-behind*/
char rotationFlag = 't';
/*Flag male ili velike rotacije s - mala, l - velika*/
char sizeFlag = 's';

/*Promenljiva za randomizaciju*/
int randomizeCount = 20;

/*Promenljive za timer funkcije*/
int curentTick = 0;
int MaxTick = 9;


/*promenljive za pocetnu animaciju*/
double start_parameter=0;
static int start_ongoing=1;
static int start=1;

/*Promenljiva koja broji rotacije i koja se ispisuje na ekran*/
int number_of_moves=0;

/*Objekat Pyraminx*/
Pyramidix* PX;


static void on_keyboard(unsigned char key, int x, int y);
static void on_reshape(int width, int height);
static void on_display(void);
static void on_timer(int);
static void rotate(int degree);
static void start_timer(int value);
static void randomize();
static void on_randomizer_timer(int value);
static int randNum(int min, int max);
static void setDirection(int a, int b, int c);
static void start_display();

using namespace std;

int main(int argc,char** argv){

  PX = new Pyramidix();
  animation_ongoing = 0;

  /*Inicijalizacija random seed*/
  srand(time(0));

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
  glutDisplayFunc(start_display);

  /*Pozivanje funkcija za mis*/
  glutMouseFunc(on_mouse);
  glutMotionFunc(on_motion);
  mouse_x = 0;
  mouse_y = 0;

  glClearColor(0, 0, 0, 0);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  Image * image;

  /* Ukljucuju se teksture. */
  glEnable(GL_TEXTURE_2D);

  glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_REPLACE);

  /*Inicijalizuje se objekat*/
  image = image_init(0, 0);

  /* Generisu se identifikatori tekstura. */
  glGenTextures(2, texture);

  /* Kreira se tekstura. */
  image_read(image, FILENAME0);

  /*Kreira se prva tekstura*/
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,  GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,  GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image->width, image->height, 0,GL_RGB, GL_UNSIGNED_BYTE,image->pixels);


  image_read(image, FILENAME1);
  /*Kreira se druga tekstura*/
  glBindTexture(GL_TEXTURE_2D, texture[1]);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,  GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,  GL_CLAMP);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,image->width, image->height, 0,GL_RGB, GL_UNSIGNED_BYTE,image->pixels);

  /* Iskljucuje se tekstura */
  glBindTexture(GL_TEXTURE_2D, 0);

  /* Unistava se objekat*/
  image_done(image);

  /*Mis*/
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glGetFloatv(GL_MODELVIEW_MATRIX, matrix);

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
  gluPerspective(45, window_width / (float)window_height, 1, 20);
}

static void on_keyboard(unsigned char key, int x, int y)
{
  switch (key) {
	case 27:
		/* Zavrsava se program. */
		exit(0);
		break;
  case 's':
  case 'S':
    if(start){
      start=0;
      glutDisplayFunc(on_display);
      glutIdleFunc(on_display);
      /*Pokrece se pocetna animacija*/
      if(start_ongoing)
          glutTimerFunc(START_TIMER_INT, start_timer, START_TIMER_ID);
    }
    break;
	case 'q':
    if (!animation_ongoing) {
      directionFlag = 'r';
			sizeFlag = 'l';
			rotationFlag ='t';
      animation_ongoing = 1;
      number_of_moves++;
			glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'Q':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 'l';
      rotationFlag = 't';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'w':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 'l';
      rotationFlag = 'l';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'W':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 'l';
      rotationFlag = 'l';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'e':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 'l';
      rotationFlag = 'r';
      animation_ongoing = 1;
      number_of_moves++;
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
	case 't':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 'l';
      rotationFlag = 'b';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case 'T':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 'l';
      rotationFlag = 'b';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '1':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 's';
      rotationFlag = 't';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '!':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 's';
      rotationFlag = 't';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '2':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 's';
      rotationFlag = 'l';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '@':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 's';
      rotationFlag = 'l';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '3':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 's';
      rotationFlag = 'r';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '#':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 's';
      rotationFlag = 'r';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '4':
    if (!animation_ongoing) {
      directionFlag = 'r';
      sizeFlag = 's';
      rotationFlag = 'b';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
	case '$':
    if (!animation_ongoing) {
      directionFlag = 'l';
      sizeFlag = 's';
      rotationFlag = 'b';
      animation_ongoing = 1;
      number_of_moves++;
      glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
    }
		break;
  case 'r':
	case 'R':
		if (!animation_ongoing) {
			randomizeCount = 20;
			randomize();
		}
    break;
  case 'n':
  case 'N':
    delete PX;
    PX=new Pyramidix();
    number_of_moves=0;
    glutPostRedisplay();
    break;
	}
}


static void on_display(void)
{

	/* Brise se prethodni sadrzaj prozora. */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0);

  /*Postavljanje osvetljenja*/
	GLfloat light_ambient[] = { 0.0, 0.0, 0.0, 1 };
	GLfloat light_diffuse[] = { 1, 1, 1, 1 };
	GLfloat light_specular[] = { 0.9, 0.9, 0.9, 1 };

  /*Ukljucivanje osvetljenja*/
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);

  /* Postavlja se pozadina*/
  glBindTexture(GL_TEXTURE_2D, texture[0]);
  glBegin(GL_QUADS);
      glNormal3f(0, 0, 1);

      glTexCoord2f(0, 0);
      glVertex3f(-3.8, -3.8,- 2);

      glTexCoord2f(1, 0);
      glVertex3f(3.8, -3.8,- 2);

      glTexCoord2f(1, 1);
      glVertex3f(3.8, 3.8, -2);

      glTexCoord2f(0, 1);
      glVertex3f(-3.8, 3.8, -2);
  glEnd();

  /* Iskljucujemo teksturu */
  glBindTexture(GL_TEXTURE_2D, 0);

  /*Postavlja se pogled na piramidu*/
  glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
  gluLookAt(0, 0, 12-start_parameter*5, 0, 0, 0, 0, 1, 0);

  /*Prekida se pocetna animacija*/
  if(start_parameter>=1)
    start_ongoing=0;

  /*Ispisivanje promenljive number_of_moves na ekran*/
  string s="Number of moves: ";
  s+=to_string(number_of_moves);
  glRasterPos2f(-2.7,2.3);
  int len = s.length();
  for (int i = 0; i < len; i++) {
    glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, s[i]);
  }

  /*Matrica za mis*/
  glMultMatrixf(matrix);

  /*Crtanje piraminx-a*/
	PX->Draw();

  /*Postavljanje kratke rotacije prilikom pocetne animacije*/
  if(start_parameter >=0.4 && start_parameter<=1)
    PX->RotationOnY+=1;

	glutSwapBuffers();
}

/*Funkcija za rotacije delova Pyraminx-a*/
static void rotate(int degree)
{
	if (sizeFlag == 's')
	{
		switch (rotationFlag)
		{
			case 't' : PX->RotateTop(degree);
				break;
			case 'l': PX->RotateBottomLeft(degree);
				break;
			case 'r': PX->RotateBottomRight(degree);
				break;
			case 'b': PX->RotateBottomBehind(degree);
				break;
		}
	}
	else
	{
		switch (rotationFlag)
		{
		case 't': PX->RotateTopBig(degree);
			break;
		case 'l': PX->RotateBottomLeftBig(degree);
			break;
		case 'r': PX->RotateBottomRightBig(degree);
			break;
		case 'b': PX->RotateBottomBehindBig(degree);
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
  /*Ukoliko je curentTick veci od MaxTick prekida se animacija za rotaciju*/
  if (curentTick > MaxTick) {
    animation_ongoing = 0;
    curentTick = 0;
    return;
  }

  /* Forsira se ponovno iscrtavanje prozora*/
  glutPostRedisplay();

  /* Po potrebi se ponovo postavlja tajmer*/
  if (animation_ongoing) {
    glutTimerFunc(TIMER_INTERVAL, on_timer, TIMER_ID);
  }
}

/*Mis*/
static void on_mouse(int button, int state, int x, int y){
    mouse_x = x;
    mouse_y = y;
}
static void on_motion(int x, int y)
{
    int delta_x, delta_y;

    delta_x = x - mouse_x;
    delta_y = y - mouse_y;

    mouse_x = x;
    mouse_y = y;

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
        glLoadIdentity();
        glRotatef(180 * (float) delta_x / window_width, 0, 1, 0);
        glRotatef(180 * (float) delta_y / window_height, 1, 0, 0);
        glMultMatrixf(matrix);
        glGetFloatv(GL_MODELVIEW_MATRIX, matrix);
    glPopMatrix();

    glutPostRedisplay();
}

/*tajmer za pocetnu animaciju*/
static void start_timer(int value){

    if(value!=START_TIMER_ID){
        return;
    }

    start_parameter+=0.01;

    glutPostRedisplay();

    if(start_ongoing){
        glutTimerFunc(START_TIMER_INT, start_timer, START_TIMER_ID);
    }
}

/*tajmer za randomizaciju*/
static void on_randomizer_timer(int value)
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
		randomizeCount--;
		randomize();
		return;
	}

	glutPostRedisplay();

  if (animation_ongoing) {
		glutTimerFunc(TIMER_INTERVAL, on_randomizer_timer, TIMER_ID);
	}
}

/*Vraca random broj iz intervala [min,max]*/
static int randNum(int min, int max)
{
  int range = max - min + 1;
  int num = rand() % range + min;
  return num;
}

/*Postavlja parametre za rotaciju gde d predtsvlja directionFlag,sF sizeFlag i rF rotationFlag*/
static void setDirection(int d, int sF, int rF) {

	if (d == 0) {
		directionFlag = 'l';
	}
	else {
		directionFlag = 'r';
	}
	if (sF == 0) {
		sizeFlag = 'l';
	}
	else {
		sizeFlag = 's';
	}
	if (rF == 0) {
		rotationFlag = 'b';
	}
	else if (rF == 1) {
		rotationFlag = 'l';
	}
	else if (rF == 2) {
		rotationFlag = 'r';
	}
	else {
		rotationFlag = 't';
	}
}

/*Funcija koja vrsi randomizaciju Pyraminx-a*/
static void randomize() {
	if (randomizeCount < 1)
    return;
	if (!animation_ongoing) {
		int d = randNum(0, 1);
		int sF = randNum(0, 1);
		int rF = randNum(0, 3);
		setDirection(d, sF, rF);
		animation_ongoing = 1;
		glutTimerFunc(TIMER_INTERVAL, on_randomizer_timer, TIMER_ID);
	}
}
/*Pocetna slika*/
static void start_display(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0, 0, 7, 0, 0, 0, 0, 1, 0);

	  glBindTexture(GL_TEXTURE_2D, texture[1]);

    glBegin(GL_QUADS);
        glNormal3f(0, 0, 1);

        glTexCoord2f(0, 0);
        glVertex3f(-3.8,-3.8,- 2);

        glTexCoord2f(1, 0);
        glVertex3f(3.8, -3.8,- 2);

        glTexCoord2f(1, 1);
        glVertex3f(3.8, 3.8, -2);

        glTexCoord2f(0, 1);
        glVertex3f(-3.8, 3.8, -2);
    glEnd();

    glutSwapBuffers();

}
