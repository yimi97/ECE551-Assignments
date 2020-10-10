#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "point.hpp"
class Circle {
 private:
  Point p;
  const double r;

 public:
  Circle(Point np, const double nr) : p(np), r(nr) {}
  void move(double dx, double dy) { p.move(dx, dy); }
  double intersectionArea(const Circle & otherCircle);
  ~Circle() {}
};
