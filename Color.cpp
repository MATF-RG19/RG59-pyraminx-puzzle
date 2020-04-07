#include "Color.h"
#include <GL/glut.h>

void SetRed() {
	GLfloat mat_ambient[] = { 0.1745f, 0.01175f, 0.01175f, 0.55f };
	GLfloat mat_diffuse[] = { 0.61424f, 0.04136f, 0.04136f, 0.55f };
	GLfloat mat_specular[] = { 0.727811f, 0.626959f, 0.626959f, 0.55f };
	GLfloat shine[] = { 76.8f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}
void SetGreen() {
	GLfloat mat_ambient[] = { 0.0215f, 0.1745f, 0.0215f, 0.55f };
	GLfloat mat_diffuse[] = { 0.07568f, 0.61424f, 0.07568f, 0.55f };
	GLfloat mat_specular[] = { 0.633f, 0.727811f, 0.633f, 0.55f };
	GLfloat shine[] = { 76.8f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}
void SetBlue() {
	GLfloat mat_ambient[] = { 0.0f,0.1f,0.06f ,1.0f };
	GLfloat mat_diffuse[] = { 0.0f,0.50980392f,0.50980392f,1.0f };
	GLfloat mat_specular[] = { 0.50196078f,0.50196078f,0.50196078f,1.0f };
	GLfloat shine[] = { 32.0f };


	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}

void SetYellow() {
	GLfloat mat_ambient[] = { 0.24725f, 0.1995f, 0.0745f, 1.0f };
	GLfloat mat_diffuse[] = { 0.75164f, 0.60648f, 0.22648f, 1.0f };
	GLfloat mat_specular[] = { 0.628281f, 0.555802f, 0.366065f, 1.0f };
	GLfloat shine[] = { 51.2f };

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}
void SetBlack() {
	GLfloat mat_ambient[] = {0.0f, 0.0f, 0.0f, 1.0f};
	GLfloat mat_diffuse[] = {0.01f, 0.01f, 0.01f, 1.0f};
	GLfloat mat_specular[] = {0.50f, 0.50f, 0.50f, 1.0f };
	GLfloat shine[] = { 32.0f};

	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
	glMaterialfv(GL_FRONT, GL_SHININESS, shine);
}

void SetColor(Color color)
{

	switch (color)
	{
	case Red:
			SetRed();
			break;
	case Green:
		SetGreen();
		break;
	case Blue:
			SetBlue();
			break;
	case Yellow:
		SetYellow();
		break;
	default:
		SetBlack();
		break;
	}
}
