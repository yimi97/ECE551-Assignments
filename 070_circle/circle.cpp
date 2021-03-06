#include "circle.hpp"
#define PI 3.14159285
double Circle::intersectionArea(const Circle & otherCircle) {
  double d = p.distanceFrom(otherCircle.p);
  double r1, r2;
  if (r <= otherCircle.r) {
    r1 = r;
    r2 = otherCircle.r;
  }
  else {
    r1 = otherCircle.r;
    r2 = r;
  }
  if (r1 + r2 <= d) {
    return 0;
  }
  if (r2 - r1 >= d) {
    return r1 * r1 * PI;
  }
  double x = (-r2 * r2 + r1 * r1 + d * d) / (2 * d);
  double y = (r2 * r2 - r1 * r1 + d * d) / (2 * d);
  double rad1 = (acos(x / r1) * r1 * r1);
  double rad2 = (acos(y / r2) * r2 * r2);
  double diamond = sqrt(r2 * r2 - y * y) * d;

  return rad1 + rad2 - diamond;
}
