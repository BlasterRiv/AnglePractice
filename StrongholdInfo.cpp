#include "StrongholdInfo.h"
#include "point.h"
#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>
Point const StrongholdInfo::origin = {0, 0};

double StrongholdInfo::randD(double min, double max) {
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_real_distribution<double> distr(min, max);
  return distr(generator);
}
int StrongholdInfo::getZPoint(double angle, int x) {
  return tan(angle * M_PI / 180.0) * x;
}
float StrongholdInfo::getAngle(Point sec_pt, Point ft_pt) {
  return atan2(ft_pt.x - sec_pt.x, sec_pt.z - ft_pt.z) * 180.0 / M_PI;
}

StrongholdInfo::StrongholdInfo() {
  first_stronghold, sec_stronghold, third_stonghold = {-1, -1};
  minecraftOffset = -M_PI_2;
  std::cout << "\n minecraftOffset: " << minecraftOffset;
}
void StrongholdInfo::generateStrongholds() {
  double rand_dis = randD(1280, 2816);
  double theta = randD(0, 2.0 * M_PI) + minecraftOffset;
  first_stronghold = {int(rand_dis * -sin(theta)), int(rand_dis * cos(-theta))};
  std::cout << rand_dis << " x: " << first_stronghold.x
            << " z: " << first_stronghold.z << " " << rand_dis * -sin(theta);
  // float angle = getAngle(first_stronghold);
  // float angle = atan2(first_stronghold.z, first_stronghold.x) * 180.00 /
  // M_PI;
  double angle = theta * (180.0 / M_PI);
  std::cout << "Angle: " << angle << "/" << theta;
  //   randomx within  IRX ORx
  int randomx = int(randD(1280, 2816) * -sin(theta - (120.00 * M_PI / 180.0)));
  sec_stronghold = {randomx, getZPoint((angle - 120.00), randomx)};
  randomx = (randD(1280, 2816) * -sin(theta - (240.00 * M_PI / 180.0)));
  //  randomx within  IRX ORx
  third_stonghold = {randomx, getZPoint(angle - 240.00, randomx)};
  sec_stronghold.print_point();
  third_stonghold.print_point();
}
Point StrongholdInfo::getClosestStronghold(Point curLoc) {
  int dis_to_first = sqrt(pow(first_stronghold.x - curLoc.x, 2) +
                          pow(first_stronghold.z - curLoc.z, 2));
  int dis_to_sec = sqrt(pow(first_stronghold.x - curLoc.x, 2) +
                        pow(first_stronghold.z - curLoc.z, 2));

  int dis_to_third = sqrt(pow(first_stronghold.x - curLoc.x, 2) +
                          pow(first_stronghold.z - curLoc.z, 2));
  if (dis_to_first <= dis_to_sec && dis_to_first <= dis_to_third) {
    return first_stronghold;
  } else if (dis_to_sec <= dis_to_third) {
    return sec_stronghold;
  } else { // else if //else cheack error
    return third_stonghold;
  }
}
double StrongholdInfo::getAngleOfClosestStronghold(Point curLoc) {
  Point closest = getClosestStronghold(curLoc);
  return atan2(closest.x - curLoc.x, curLoc.z - closest.z) * 180.0 / M_PI;
}
Point StrongholdInfo::getFistStronghold() { return first_stronghold; }
Point StrongholdInfo::getSecStronghold() { return sec_stronghold; }
Point StrongholdInfo::getThdStronghold() { return third_stonghold; }
