#include "Point.h"
#include "Color.h"
#pragma once
class Triangle
{
public:
	Point p1, p2, p3;
	Color color;
	Triangle();
	bool reverseNormal;
	Triangle(Point pp1, Point pp2, Point pp3, Color c1);
	void Draw();
};
