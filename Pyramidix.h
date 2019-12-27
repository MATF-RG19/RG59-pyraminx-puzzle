#include "Pyramid.h"
#pragma once
class Pyramidix
{
private:


  //Ugao rotacije male piramide
	int saFLB, saFLR, saLRB, saFRB;

  //Ugao rotacije velike piramide
	int aFLB, aFLR, aLRB, aFRB;

  //Piramide gde su tri strane vidljive,nakon prefiksa p3 su slova koja predstavljaju orijentaciju,tj gde se nalazi piramida
	Pyramid p3FLB, p3FLR, p3FRB, p3LRB;

  //Piramide sa dve vidljive strane,nakon prefiksa p2 su slova koja predstavljaju orijentaciju,tj gde se nalazi piramida
	Pyramid p2FL, p2FR, p2FB, p2LR, p2LB, p2RB;


	//F - initialy on front, L - left, R- right, B - bottom

	Triangle tFLB, tFLR, tFRB, tLFB, tLFR, tLRB, tRFL, tRFB, tRLB, tBFL, tBFR, tBLR;

	Point cFLB, cFLR, cFRB, cLRB;
	Point vFLB, vFLR, vFRB, vLRB;
  Pyramid *pp2FL, *pp2FR, *pp2FB, *pp2LR, *pp2LB, *pp2RB;

public:
	int RotationOnX, RotationOnY, RotationOnZ;

	Pyramidix();

	void RotateTop(int angle);
	void RotateTopBig(int angle);
	void RotateBottomLeft(int angle);
	void RotateBottomLeftBig(int angle);
	void RotateBottomRight(int angle);
	void RotateBottomRightBig(int angle);
	void RotateBottomBehind(int angle);
	void RotateBottomBehindBig(int angle);


	void Draw(void);
};
