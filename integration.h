#ifndef INTEGRATION_H
#define INTEGRATION_H

#include <vector>
#include <cmath>
#include <iostream>
#include <fstream>

#include "body.h"
#include "vector3d.h"

class RK4 {
  public:
    RK4(std::vector<Body>, double);

    std::vector<Body> bodies;
    double time_step;

    void gravity_step();

    Vector3D single_body_accel(int);

    Vector3D partial_step(Vector3D&, Vector3D&, double);

    void update_velocity();

    void update_position();

    void log_state(std::ofstream& os);
};

#endif
