#include "Pyramid.h"
#include <math.h>

Pyramid::Pyramid()
{
	PointDownLeft = Point();
	PointDownRight = Point();
	PointDownMiddle = Point();
	PointUp = Point();

}
/*Kreiranje pirammide uz pomoc donje leve tacke*/
Pyramid::Pyramid(Point PointDownLeft1)
{
	PointDownLeft = Point(PointDownLeft1);
	PointDownRight = Point(PointDownLeft1.x + 1.0f, PointDownLeft1.y, PointDownLeft1.z);
	PointDownMiddle = Point(PointDownLeft1.x + 0.5f, PointDownLeft1.y, PointDownLeft1.z + sqrt(3)/2);
	PointUp = Point(PointDownLeft1.x + 0.5f, PointDownLeft1.y + sqrt(6)/3, PointDownLeft1.z + sqrt(3)/6 );
}
/*Kreiranje piramide uz pomoc 4 tacke*/
Pyramid::Pyramid(Point PointDownLeft1, Point PointDownRight1, Point PointDownMiddle1, Point PointUp1)
{
	PointDownLeft = Point(PointDownLeft1);
	PointDownRight = Point(PointDownRight1);
	PointDownMiddle = Point(PointDownMiddle1);
	PointUp = Point(PointUp1);
}

void Pyramid::Draw()
{

	Triangle(PointDownLeft, PointDownRight, PointDownMiddle, Red).Draw();
	Triangle(PointDownLeft, PointDownMiddle, PointUp, Blue).Draw();
	Triangle(PointDownLeft, PointDownRight, PointUp, Green).Draw();
	Triangle(PointUp, PointDownRight, PointDownMiddle, Yellow).Draw();

}
