#include "Triangle.h"



Triangle::Triangle()
{
	color = Red;
	reverseNormal = false;
}

Triangle::Triangle(Point pp1, Point pp2, Point pp3, Color c1)
{
	p1 = Point(pp1);
	p2 = Point(pp2);
	p3 = Point(pp3);
	reverseNormal = false;
	color = c1;

}

void Triangle::Draw()
{

	glBegin(GL_TRIANGLES);
		SetColor(color);
		//postavljanje normala
		if (reverseNormal) {
			glNormal3f(-(p2.y - p1.y) * (p3.z - p1.z) + (p3.y - p1.y) * (p2.z - p1.z), -(p3.x - p1.x) * (p2.z - p1.z) + (p2.x - p1.x) * (p3.z - p1.z), -(p2.x - p1.x) * (p3.y - p1.y) + (p3.x - p1.x) * (p2.y - p1.y));
		}
		else {
			glNormal3f((p2.y - p1.y) * (p3.z - p1.z) - (p3.y - p1.y) * (p2.z - p1.z), (p3.x - p1.x) * (p2.z - p1.z) - (p2.x - p1.x) * (p3.z - p1.z), (p2.x - p1.x) * (p3.y - p1.y) - (p3.x - p1.x) * (p2.y - p1.y));
		}
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);
		glVertex3f(p3.x, p3.y, p3.z);
	glEnd();

  /*Iscrtavanje linija oko trougla*/
	glLineWidth(2);
	SetColor(Black);
	glBegin(GL_LINES);
		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p2.x, p2.y, p2.z);

		glVertex3f(p1.x, p1.y, p1.z);
		glVertex3f(p3.x, p3.y, p3.z);

		glVertex3f(p3.x, p3.y, p3.z);
		glVertex3f(p2.x, p2.y, p2.z);
	glEnd();
}
