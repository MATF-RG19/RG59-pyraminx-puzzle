#include "Triangle.h"
class Pyramid
{
public:
	Point PointDownLeft, PointDownRight, PointDownMiddle, PointUp;
	Pyramid();
	Pyramid(Point PointDownLeft);
	Pyramid(Point PointDownLeft, Point PointDownRight, Point PointDownMiddle, Point PointUp);
  void Draw();
};
