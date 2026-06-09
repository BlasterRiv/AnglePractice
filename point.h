#ifndef point_H
#define point_H
#include <iostream>
struct Point {
  int x, z;
  void print_point() { std::cout << "x: " << x << " z: " << z << "\n"; }
};
#endif
