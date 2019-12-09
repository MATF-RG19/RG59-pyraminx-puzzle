#include "Pyramid.h"
#include <math.h>

Pyramid::Pyramid()
{
	PointDownLeft = Point();
	PointDownRight = Point();
	PointDownMiddle = Point();
	PointUp = Point();
	Draw();
}
/*Kreiranje pirammide uz pomoc donje leve tacke*/
Pyramid::Pyramid(Point PointDownLeft1)
{
	PointDownLeft = Point(PointDownLeft1);
	PointDownRight = Point(PointDownLeft1.x + 1.0f, PointDownLeft1.y, PointDownLeft1.z);
	PointDownMiddle = Point(PointDownLeft1.x + 0.5f, PointDownLeft1.y, PointDownLeft1.z - sqrt(3)/2);
	PointUp = Point(PointDownLeft1.x + 0.5f, PointDownLeft1.y + sqrt(3)/2, PointDownLeft1.z - sqrt(3)/6 );
	Draw();
}
/*Kreiranje piramide uz pomoc 4 tacke*/
Pyramid::Pyramid(Point PointDownLeft1, Point PointDownRight1, Point PointDownMiddle1, Point PointUp1)
{
	PointDownLeft = Point(PointDownLeft1);
	PointDownRight = Point(PointDownRight1);
	PointDownMiddle = Point(PointDownMiddle1);
	PointUp = Point(PointUp1);
	Draw();
}

void Pyramid::Draw()
{
	Triangle draw = Triangle(PointDownLeft, PointDownRight, PointDownMiddle, Red);
	draw = Triangle(PointDownLeft, PointDownMiddle, PointUp, Blue);
	draw = Triangle(PointDownLeft, PointDownRight, PointUp, Green);
	draw = Triangle(PointUp, PointDownRight, PointDownMiddle, Yellow);
}
