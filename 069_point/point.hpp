#include <math.h>
#include <stdio.h>
#include <stdlib.h>
class Point {
 private:
  double x;
  double y;

 public:
  Point() : x(0), y(0) {}
  void move(double dx, double dy) {
    x += dx;
    y += dy;
  }
  double distanceFrom(const Point & p) {
    double res = sqrt(pow((x - p.x), 2) + pow((y - p.y), 2));
    return res;
  }
  //  ~Point() {}
};
