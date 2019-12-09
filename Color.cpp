#include "Color.h"
#include <GL/glut.h>

void SetColor(Color color)
{
	switch (color)
	{
	case Red:
		glColor3f(1, 0, 0);
		break;
	case Green:
		glColor3f(0, 1, 0);
		break;
	case Blue:
		glColor3f(0, 0, 1);
		break;
	case Yellow:
		glColor3f(1, 1, 0);
		break;
	default:
		glColor3f(0, 0, 0);
		break;
	}
}
