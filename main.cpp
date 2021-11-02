#include <cstdio>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "body.h"
#include "integration.h"
#include "vector3d.h"

int main() {
  const double time_step = 0.1;
  const int max_time = 5000;
  const int max_steps = max_time / time_step;
  const int points_per_body = 1000;
  const int log_resolution = max_steps / points_per_body;

  std::vector<Body> bodies;
  bodies.push_back(Body(Vector3D(0, 0, 0), Vector3D(0, 0, -1e-2), 1e6));
  bodies.push_back(Body(Vector3D(0, 1, 0), Vector3D(1e-2, 1e-3, 0), 1e6));
  bodies.push_back(Body(Vector3D(0, 0, 1), Vector3D(-1e-3, 0, 1e-3), 1e5));

  // std::default_random_engine generator;
  // std::uniform_real_distribution<double> distribution(-1.0, 1.0);
  //
  // int nbodies = 100;
  // for (int i = 0; i < nbodies; i++) {
  //   double x = distribution(generator) * 2;
  //   double y = distribution(generator) * 2;
  //   double z = distribution(generator) * 2;
  //   double vx = distribution(generator) * 1e-3;
  //   double vy = distribution(generator) * 1e-3;
  //   double vz = distribution(generator) * 1e-3;
  //   double m = 1e5;
  //
  //   bodies.push_back(Body(Vector3D(x, y, z), Vector3D(vx, vy, vz), m));
  // }

  std::ofstream output("output.csv", std::ios::out);

  RK4 simulation(bodies, time_step);

  for (int i = 0; i < max_steps; i++) {
    printf("\r%d / %d (%0.1f%%)", i + 1, max_steps,
           (float)(i + 1) / max_steps * 100);
    std::fflush(stdout);

    simulation.gravity_step();
    if (i % log_resolution == 0) simulation.log_state(output);
  }
  printf("\n");

  return 0;
}
