/* write your class interface in this file
   write function definitions only if they are very short
 */
#include <stdio.h>
#include <stdlib.h>

#include <cmath>

using namespace std;
class Vector2D {
 private:
  double x;
  double y;

 public:
  void initVector(double newx, double newy) {
    x = newx;
    y = newy;
  }

  double getMagnitude() const { return sqrt(x * x + y * y); }

  Vector2D operator+(const Vector2D & rhs) const {
    Vector2D ans;
    ans.x = x + rhs.x;
    ans.y = y + rhs.y;
    return ans;
  }
  Vector2D & operator+=(const Vector2D & rhs) {
    x += rhs.x;
    y += rhs.y;
    return *this;
  }
  double dot(const Vector2D & rhs) const { return x * rhs.x + y * rhs.y; }
  void print() const { printf("<%.2f, %.2f>", x, y); }
};
