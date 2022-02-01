#include "body.h"

Body::Body(Vector3D position, Vector3D velocity, double mass)
    : position(position), velocity(velocity), mass(mass){};

std::ostream &operator<<(std::ostream &os, const Body &body) {
  os << "Body(" << body.position << ", " << body.velocity << ", " << body.mass
     << ")";

  return os;
}
