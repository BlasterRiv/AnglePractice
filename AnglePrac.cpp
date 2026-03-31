#include "StrongholdInfo.h"
#include <bitset>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <random>
#include <string>
struct eyeInfo {
  // int x, z;
  Point current_location;
  std::bitset<4> posNeg;
  float axis;
  float firstAngle, secondAngle;

  int xShift, zShift;
  Point Ans;
};
void displayInfo(eyeInfo info) {
  std::cout << std::fixed;
  std::cout << "\033[36m";
  std::cout << "Curent cords: x: " << info.current_location.x
            << " z: " << info.current_location.z << "\n";
  std::string xNeg = "x";
  std::string zNeg = "z";
  if (info.posNeg[0])
    xNeg = "-x";
  if (info.posNeg[1])
    zNeg = "-z";
  std::cout << "Major cord: ";
  std::cout << (info.posNeg[2] ? zNeg.append(" minor chord: ").append(xNeg)
                               : xNeg.append(" minor chord: ").append(zNeg));

  std::cout << "\n";
  std::cout << "angles: " << std::setprecision(2) << info.firstAngle << " "
            << info.secondAngle << "\n";
  std::cout << "axis: " << info.axis << "\n" << "\033[0m";
  ;
}
void displayAns(eyeInfo info) {
  std::cout << "\033[31m";
  std::cout << "shift: " << info.xShift << " " << info.zShift << "\n";
  std::cout << "answer x: " << info.Ans.x << " z: " << info.Ans.z << "\033[0m";
  std::cout << "\n" << "-------" << "\n";
}
int randomR(int range_from, int range_to) {
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<int> distr(range_from, range_to);
  return distr(generator);
}
int main(int argc, char *argv[]) {
  bool playing = true;
  unsigned seed = time(0);
  srand(seed);
  StrongholdInfo stronghold_info;
  stronghold_info.generateStrongholds();
  while (playing) {

    eyeInfo info;

    info.current_location.x = randomR(-250, 250);
    info.current_location.z = randomR(-250, 250);
    info.firstAngle =
        stronghold_info.getAngleOfClosestStronghold(info.current_location);
    int randd = randomR(-500, 500);
    info.secondAngle = info.firstAngle + randomR(-28, 28);
    info.axis = randomR(0, 8) / 1.0;
    // int r = randomR(0, 3);
    int majShift = 200 / std::abs(info.firstAngle - info.secondAngle);
    int minShift = majShift * (info.axis / 8.0);

    info.xShift = (1 - (info.posNeg[0] * 2)) * ((majShift * ~(info.posNeg[2])) +
                                                (minShift * (info.posNeg[2])));
    info.zShift = (1 - (info.posNeg[1] * 2)) * ((majShift * (info.posNeg[2])) +
                                                (minShift * ~(info.posNeg[2])));

    info.Ans = stronghold_info.getClosestStronghold(info.current_location);
    displayInfo(info);
    int xCords;
    std::cout << "Enter xCords: \n";
    std::cin >> xCords;

    int zCords;
    std::cout << "Enter zCords: \n";
    std::cin >> zCords;
    if ((xCords == info.Ans.x) && (zCords == info.Ans.z)) {
      std::cout << "correct \n";
    } else if (abs(info.Ans.x - xCords) < 16 && abs(info.Ans.z - zCords) < 16) {
      std::cout << "Close! \n";
      displayAns(info);
    } else {
      std::cout << "incorrect \n";
      displayAns(info);
      std::cout << "-------" << "\n";
    }
  }

  return 0;
}
