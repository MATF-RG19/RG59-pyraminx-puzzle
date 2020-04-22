#include "Pyramidix.h"


using namespace std;
Pyramidix::Pyramidix()
{
	saFLB = 0;
	saFLR = 0;
	saLRB = 0;
	saFRB = 0;

	aFLB = 0;
	aFLR = 0;
	aLRB = 0;
	aFRB = 0;

	RotationOnX = 0;
	RotationOnY = 0;
	RotationOnZ = 0;

	p3FLB = Pyramid(Point(0.0f, 0.0f, 0.0f));
	p2FB = Pyramid(p3FLB.PointDownRight);
	p2LB = Pyramid(p3FLB.PointDownMiddle);
	p2RB = Pyramid(p2LB.PointDownRight);
	p3LRB = Pyramid(p2LB.PointDownMiddle);
	p3FRB = Pyramid(p2FB.PointDownRight);

	p2FL = Pyramid(p3FLB.PointUp);
	p2FR = Pyramid(p2FL.PointDownRight);
	p2LR = Pyramid(p2FL.PointDownMiddle);

	p3FLR = Pyramid(p2FL.PointUp);


	cFRB = Point(2.5f, sqrt(6) / 12, sqrt(3) / 6);
	cFLB = Point(0.5f, sqrt(6) / 12, sqrt(3) / 6);
	cFLR = Point(1.5f, 0.0f, sqrt(3) / 2);
	cLRB = Point(1.5f, 0, 3 *  sqrt(3) / 2);

	vFRB = Point(-0.5f, sqrt(6) / 12, sqrt(3) / 6);
	vFLB = Point(0.5f, sqrt(6) / 12, sqrt(3) / 6);
	vFLR = Point(0.0f, 1.0f, 0.0f);
	vLRB = Point(0.0f, -sqrt(6) / 12, sqrt(3) / 3);

	tFLB = Triangle(p3FLB.PointDownRight, p3FLB.PointUp, p2FB.PointUp, Green);
	tFRB = Triangle(p2FB.PointDownRight, p2FB.PointUp, p3FRB.PointUp, Green);
	tFLR = Triangle(p2FL.PointDownRight, p2FL.PointUp, p2FR.PointUp, Green);

	/*Zbog osvetljenja plavi trouglovi imaju suprotnu normalu*/
	tLFB = Triangle(p3FLB.PointDownMiddle, p3FLB.PointUp, p2LB.PointUp, Blue);
	tLFB.reverseNormal=true;
	tLRB = Triangle(p2LB.PointDownMiddle, p2LB.PointUp, p3LRB.PointUp, Blue);
	tLRB.reverseNormal=true;
	tLFR = Triangle(p2FL.PointDownMiddle, p2FL.PointUp, p2LR.PointUp, Blue);
	tLFR.reverseNormal=true;

	tRFB = Triangle(p3FRB.PointDownMiddle, p3FRB.PointUp, p2RB.PointUp, Yellow);
	tRLB = Triangle(p2RB.PointDownMiddle, p2RB.PointUp, p3LRB.PointUp, Yellow);
	tRFL = Triangle(p2FR.PointDownMiddle, p2FR.PointUp, p2LR.PointUp, Yellow);

	/*Zbog osvetljenja crveni trouglovi imaju suprotnu normalu*/
	tBFL = Triangle(p3FLB.PointDownRight, p3FLB.PointDownMiddle, p2FB.PointDownMiddle, Red);
	tBFL.reverseNormal=true;
	tBFR = Triangle(p2FB.PointDownRight, p2FB.PointDownMiddle, p3FRB.PointDownMiddle, Red);
	tBFR.reverseNormal=true;
	tBLR = Triangle(p2LB.PointDownRight, p2LB.PointDownMiddle, p2RB.PointDownMiddle, Red);
	tBLR.reverseNormal=true;

	pp2FB = &p2FB;
	pp2FR = &p2FR;
	pp2FL = &p2FL;
	pp2LB = &p2LB;
	pp2LR = &p2LR;
	pp2RB = &p2RB;

}
//Rotiranje male piramide
void Pyramidix::RotateTop(int angle)
{
	//dodavanje ugla rotacije male piramide koje ce se kasniti iskoristiti pri crtanju
	saFLR += angle;

}
//Rotiranje gornje velike piramide
void Pyramidix::RotateTopBig(int angle)
{
	RotateTop(angle);
	aFLR += angle;

	//dodavanje
	RotationConfiguration testFLR = RotationConfiguration();
	testFLR.Angle = angle;
	testFLR.Center = cFLR;
	testFLR.VectorOfRotation = vFLR;

  pp2FR->AddRotation(testFLR);
	pp2FL->AddRotation(testFLR);
	pp2LR->AddRotation(testFLR);

	if (angle < 0) {
		Pyramid *test = pp2FR;
		pp2FR = pp2FL;
		pp2FL = pp2LR;
		pp2LR = test;
	}
	else {
		Pyramid *test = pp2FR;
		pp2FR = pp2LR;
		pp2LR = pp2FL;
		pp2FL = test;

	}


}

void Pyramidix::RotateBottomLeft(int angle)
{
	saFLB += angle;
	int temp = saFLB;

	if (abs(saFLB) >= 360)
		temp = abs(saFLB) % 360;
	if (saFLB < 0)
		temp = -temp;
}

void Pyramidix::RotateBottomLeftBig(int angle)
{
	RotateBottomLeft(angle);
	aFLB += angle;
	int temp = aFLB;

	if (abs(aFLB) >= 360)
		temp = abs(aFLB) % 360;
	if (aFLB < 0)
		temp = -temp;

	RotationConfiguration testFLB = RotationConfiguration();
	testFLB.Angle = angle;
	testFLB.Center = cFLB;
	testFLB.VectorOfRotation = vFLB;

	pp2FL->AddRotation(testFLB);
	pp2FB->AddRotation(testFLB);
	pp2LB->AddRotation(testFLB);

	if (angle < 0) {
		Pyramid *test = pp2FL;
		pp2FL = pp2LB;
		pp2LB = pp2FB;
		pp2FB = test;
	}
	else {
		Pyramid *test = pp2FL;
		pp2FL = pp2FB;
		pp2FB = pp2LB;
		pp2LB = test;

	}
}

void Pyramidix::RotateBottomRight(int angle)
{
	saFRB += angle;
	int temp = saFRB;

	if (abs(saFRB) >= 360)
		temp = abs(saFRB) % 360;
	if (saFRB < 0)
		temp = -temp;
}

void Pyramidix::RotateBottomRightBig(int angle)
{
	RotateBottomRight(angle);
	aFRB += angle;
	int temp = aFRB;

	if (abs(aFRB) >= 360)
		temp = abs(aFRB) % 360;
	if (aFRB < 0)
		temp = -temp;

	RotationConfiguration testFRB = RotationConfiguration();
	testFRB.Angle = angle;
	testFRB.Center = cFRB;
	testFRB.VectorOfRotation = vFRB;

	pp2FR->AddRotation(testFRB);
	pp2FB->AddRotation(testFRB);
	pp2RB->AddRotation(testFRB);

	if (angle < 0) {
		Pyramid* test = pp2FR;
		pp2FR = pp2FB;
		pp2FB = pp2RB;
		pp2RB = test;
		}
	else {
		Pyramid* test = pp2FR;
		pp2FR = pp2RB;
		pp2RB = pp2FB;
		pp2FB = test;

	}
}

void Pyramidix::RotateBottomBehind(int angle)
{
	saLRB += angle;
	int temp = saLRB;

	if (abs(saLRB) >= 360)
		temp = abs(saLRB) % 360;
	if (saLRB < 0)
		temp = -temp;
}

void Pyramidix::RotateBottomBehindBig(int angle)
{
	RotateBottomBehind(angle);
	aLRB += angle;
	int temp = aLRB;

	if (abs(aLRB) >= 360)
		temp = abs(aLRB) % 360;
	if (aLRB < 0)
		temp = -temp;

	RotationConfiguration testLRB = RotationConfiguration();
	testLRB.Angle = angle;
	testLRB.Center = cLRB;
	testLRB.VectorOfRotation = vLRB;

	pp2LR->AddRotation(testLRB);
	pp2RB->AddRotation(testLRB);
	pp2LB->AddRotation(testLRB);

	if (angle < 0) {
		Pyramid* test = pp2LR;
		pp2LR = pp2LB;
		pp2LB = pp2RB;
		pp2RB = test;
	}
	else {
		Pyramid* test = pp2LR;
		pp2LR = pp2RB;
		pp2RB = pp2LB;
		pp2LB = test;
	}
}


void Pyramidix::Draw()
{
	/*Translacija na centar*/
	glTranslatef(-1.5f, -sqrt(6) / 4, -sqrt(3) / 2);

	/*Rotacija oko osa*/
	glTranslatef(1.5f, sqrt(6) / 4, sqrt(3) / 2);
	glRotatef(RotationOnX, 1.0f, 0.0f, 0.0f);
	glRotatef(RotationOnY, 0.0f, 1.0f, 0.0f);
	glRotatef(RotationOnZ, 0.0f, 0.0f, 1.0f);
	glTranslatef(-1.5f, -sqrt(6) / 4, -sqrt(3) / 2);

	glPushMatrix();
	glTranslatef(0.5f, sqrt(6) / 12, sqrt(3) / 6);
	glRotatef(saFLB, 0.5f, sqrt(6) / 12, sqrt(3) / 6);
	glTranslatef(-0.5f, -sqrt(6) / 12, -sqrt(3) / 6);
	p3FLB.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5f, 0.0f, sqrt(3) / 2);
	glRotatef(saFLR, 0.0f, 1.0f, 0.0f);
	glTranslatef(-1.5f, 0.0f, -sqrt(3) / 2);
	p3FLR.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5f, sqrt(6) / 12, sqrt(3) / 6);
	glRotatef(saFRB, -0.5f, sqrt(6) / 12, sqrt(3) / 6);
	glTranslatef(-2.5f, -sqrt(6) / 12, -sqrt(3) / 6);
	p3FRB.Draw();
	glPopMatrix();

	glPushMatrix();
	glTranslatef(1.5f, 0, 3 * sqrt(3) / 2);
	glRotatef(saLRB, 0.0f, -sqrt(6) / 12, sqrt(3) / 3);
	glTranslatef(-1.5f, 0, -3 * sqrt(3) / 2);
	p3LRB.Draw();
	glPopMatrix();


	pp2LR->Draw();
	pp2FL->Draw();
	pp2FR->Draw();
	pp2FB->Draw();

	pp2LB->Draw();
	pp2RB->Draw();


	glPushMatrix();
	glTranslatef(1.5f, 0, 3 * sqrt(3) / 2);
	glRotatef(aLRB, 0.0f, -sqrt(6) / 12, sqrt(3) / 3);
	glTranslatef(-1.5f, 0, -3 * sqrt(3) / 2);
	tLRB.Draw();
	tRLB.Draw();
	tBLR.Draw();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(2.5f, sqrt(6) / 12, sqrt(3) / 6);
	glRotatef(aFRB, -0.5f, sqrt(6) / 12, sqrt(3) / 6);
	glTranslatef(-2.5f, -sqrt(6) / 12, -sqrt(3) / 6);
	tFRB.Draw();
	tRFB.Draw();
	tBFR.Draw();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(0.5f, sqrt(6) / 12, sqrt(3) / 6);
	glRotatef(aFLB, 0.5f, sqrt(6) / 12, sqrt(3) / 6);
	glTranslatef(-0.5f, -sqrt(6) / 12, -sqrt(3) / 6);
	tFLB.Draw();
	tLFB.Draw();
	tBFL.Draw();
	glPopMatrix();


	glPushMatrix();
	glTranslatef(1.5f, 0.0f, sqrt(3) / 2);
	glRotatef(aFLR, 0.0f, 1.0f, 0.0f);
	glTranslatef(-1.5f, 0.0f, -sqrt(3) / 2);
	tFLR.Draw();
	tLFR.Draw();
	tRFL.Draw();
	glPopMatrix();


}
