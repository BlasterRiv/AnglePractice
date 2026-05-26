#include "StrongholdInfo.h"
#include <bitset>
#include <cmath>
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
  std::cout << "nether shift: " << info.xShift << " " << info.zShift << "\n";
  std::cout << "answer x: " << info.Ans.x << " z: " << info.Ans.z << "\033[0m";
  std::cout << "\n" << "-------" << "\n";
}
int randomR(int range_from, int range_to) {
  std::random_device rand_dev;
  std::mt19937 generator(rand_dev());
  std::uniform_int_distribution<int> distr(range_from, range_to);
  return distr(generator);
}
enum Flags {
  isNetherChordSet = 1,
};
int main(int argc, char *argv[]) {
  bool playing = true;
  unsigned seed = time(0);
  srand(seed);
  StrongholdInfo stronghold_info;
  stronghold_info.generateStrongholds();
  while (playing) {

    eyeInfo info;

    info.current_location.x = randomR(-200, 200) * 8;
    info.current_location.z = randomR(-200, 200) * 8;
    //
    info.firstAngle =
        stronghold_info.getAngleOfClosestStronghold(info.current_location);
    info.secondAngle = stronghold_info.getAngleOfClosestStronghold(
        {info.current_location.x +
             int(28 * cos((info.firstAngle + 270) * M_PI / 180.0)),
         info.current_location.z + int(28 * -sin((info.firstAngle + 270) *
                                                 M_PI / 180.0))}); // intercept?
    //
    info.axis = fabs(fmod((info.firstAngle + 45.0), 90) - 45.0) / 5.625;
    //
    info.posNeg.set(0,
                    round((sin((info.firstAngle * M_PI / 180.0)) + 1.0) / 2.0));
    info.posNeg.set(
        1, round((cos((info.firstAngle * M_PI / 180.0) + M_PI) + 1.0) / 2.0));
    info.posNeg.set(
        2,
        round((sin(((info.firstAngle * M_PI / 180.0) * 4.0) + M_PI_2) + 1.0) /
              2.0));
    int majShift = 200.0 / std::abs(info.firstAngle - info.secondAngle);
    int minShift = majShift * (info.axis / 8.0);
    //
    info.xShift = (1 - (info.posNeg[0] * 2)) * ((majShift * ~(info.posNeg[2])) +
                                                (minShift * (info.posNeg[2])));
    info.zShift = (1 - (info.posNeg[1] * 2)) * ((majShift * (info.posNeg[2])) +
                                                (minShift * ~(info.posNeg[2])));

    info.Ans = stronghold_info.getClosestStronghold(info.current_location);
    displayInfo(info);
    int xCords;
    Point s = {info.current_location.x +
                   int(28 * cos((info.firstAngle + 270) * M_PI / 180.0)),
               info.current_location.z +
                   int(28 * -sin((info.firstAngle + 270) * M_PI / 180.0))};
    std::cout << s.x << " z " << s.z << " ";
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
