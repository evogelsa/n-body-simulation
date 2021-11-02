#ifndef BODY_H
#define BODY_H

#include <iostream>
#include <vector>

#include "vector3d.h"

class Body {
 public:
  Body(Vector3D, Vector3D, double);

  Vector3D position;
  Vector3D velocity;
  double mass;
  std::vector<Vector3D> positions;
};

std::ostream& operator<<(std::ostream&, const Body&);

#endif
