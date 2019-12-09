#include "Point.h"
#include "Color.h"

class Triangle
{
public:
	Point p1, p2, p3;
	Color color;
	Triangle();
	Triangle(Point pp1, Point pp2, Point pp3, Color c1);
	void Draw();
};
