#include "Point.h"
#pragma once
class RotationConfiguration
{
public:
  Point Center;
  int Angle;
  Point VectorOfRotation;
  RotationConfiguration();
  RotationConfiguration(Point center, int angle, Point vector);
};
