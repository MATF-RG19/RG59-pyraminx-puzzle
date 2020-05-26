#include "RotationConfiguration.h"

RotationConfiguration::RotationConfiguration()
{
	Angle = 0;
}

RotationConfiguration::RotationConfiguration(Point center, int angle, Point vector)
{
	Center = Point(center);
	Angle = angle;
	VectorOfRotation = Point(vector);
}
