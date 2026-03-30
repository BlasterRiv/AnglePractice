#pragma once
#include "point.h"
class StrongholdInfo {

private:
  Point first_stonghold, sec_stronghold, third_stonghold;
  double randD(double min, double max);
  int getZPoint(double angle, int x);
  float getAngle(Point sec_pt, Point ft_pt = origin);
  static const Point origin;

public:
  StrongholdInfo();
  void generateStrongholds();
  Point getFistStronghold();
  Point getSecStronghold();
  Point getThdStronghold();
};
