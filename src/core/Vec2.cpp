/**
 * Class for representing 2D vectors.
 *
 */
#include <iostream>
#include <math.h>
#include <ostream>

class Vec2 {
public:
  float x = 0;
  float y = 0;

  Vec2() = default;
  Vec2(float xin, float yin) : x(xin), y(yin) {}

  /**
   * Add 2 vectors operator, returing a new vector.
   *
   */
  Vec2 operator+(const Vec2 &rhs) const { return Vec2(x + rhs.x, y + rhs.y); }

  /**
   * Add a vector to an existing vector.
   *
   */
  void operator+=(const Vec2 &rhs) {
    x += rhs.x;
    y += rhs.y;
  }

  /**
   * Add a vector to an existing vector, returning
   * a reference to the object for chaining.
   *
   */
  Vec2 &add(const Vec2 &v) {
    x += v.x;
    y += v.y;
    return *this;
  }

  /**
   * Scale a vector, returning
   * a reference to the object for chaining.
   *
   */
  Vec2 &scale(float s) {
    x *= s;
    y *= s;
    return *this;
  }

  // TODO: rotate
  Vec2 &rotate(float deg) { return *this; }

  /**
   * Calculate the distnace between two vectors.
   *
   */
  float dist(const Vec2 &v) const {
    return sqrtf((v.x - x) * (v.x - x) + (v.y - y) * (v.y - y));
  }
};

int main(int argc, char *argv[]) {

  Vec2 v1(100, 200);
  Vec2 v2(50, 75);

  Vec2 v3 = v1 + v2;  // Using overloaded + operator.
  v1.add(v2).add(v3); // Using add method chaining.

  Vec2 v4(1000, 2000);
  v4 += v1;

  // v4.add(v1).scale(20.0f).rotate(90.0f);

  std::cout << v1.x << " " << v1.y << std::endl;
  std::cout << v2.x << " " << v2.y << std::endl;
  std::cout << v3.x << " " << v3.y << std::endl;
  std::cout << v4.x << " " << v4.y << std::endl;

  float dist = v1.dist(v2); // Using the dist calculation.

  std::cout << dist << std::endl;
}
