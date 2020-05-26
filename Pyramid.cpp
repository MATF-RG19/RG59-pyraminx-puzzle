#include "Pyramid.h"

Pyramid::Pyramid()
{
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

Point Pyramid::GetCenter()
{
	return Point();
}
/*Dodajemo rotacije u vector*/;
void Pyramid::AddRotation(RotationConfiguration rotation)
{
	rotations.push_back(rotation);
}

void Pyramid::Draw()
{
	glPushMatrix();
	/*Prolazimo kroz sve rotacije od kraja*/
	for(auto it = rotations.rbegin(); it != rotations.rend(); ++it){
		glTranslatef((*it).Center.x, (*it).Center.y, (*it).Center.z);
		glRotatef((*it).Angle, (*it).VectorOfRotation.x, (*it).VectorOfRotation.y, (*it).VectorOfRotation.z);
		glTranslatef(-(*it).Center.x, -(*it).Center.y, -(*it).Center.z);
	}
	Triangle(PointDownLeft, PointDownRight, PointDownMiddle, Red).Draw();
	Triangle(PointDownLeft, PointDownMiddle, PointUp, Blue).Draw();
	/*Zbog osvetljanja postavljam da zelena ima suprotnu normalu*/
	Triangle gT = Triangle(PointDownLeft, PointDownRight, PointUp, Green);
	gT.reverseNormal = true;
	gT.Draw();
	/*Zbog osvetljanja postavljam da zuta ima suprotnu normalu*/
	Triangle yT = Triangle(PointUp, PointDownRight, PointDownMiddle, Yellow);
	yT.reverseNormal = true;
	yT.Draw();
	glPopMatrix();

}
