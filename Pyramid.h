#include "Triangle.h"
#include <math.h>
#include "RotationConfiguration.h"
#include <vector>
#pragma once

using namespace std;

class Pyramid
{
public:
	Point PointDownLeft, PointDownRight, PointDownMiddle, PointUp;
	vector<RotationConfiguration> rotations = {};
	Pyramid();
	Pyramid(Point PointDownLeft);
	Pyramid(Point PointDownLeft, Point PointDownRight, Point PointDownMiddle, Point PointUp);
  void Draw();

	Point GetCenter();

	void AddRotation(RotationConfiguration rotation);
};
