#pragma once
#include "point.h"
class StrongholdInfo {

public:
  StrongholdInfo();
  void generateStrongholds();
  double getAngleOfClosestStronghold(Point curLoc);
  Point getClosestStronghold(Point curLoc);
  Point getFistStronghold();
  Point getSecStronghold();
  Point getThdStronghold();

private:
  Point first_stronghold, sec_stronghold, third_stonghold;
  double randD(double min, double max);
  int getZPoint(double angle, int x);
  float getAngle(Point sec_pt, Point ft_pt = origin);
  static const Point origin;
};
