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
  const int max_time = 365*24*60*60;
  const unsigned long long max_steps = max_time / time_step;
  const int points_per_body = 10000;
  const int log_resolution = max_steps / points_per_body;

  std::vector<Body> bodies;

  // sun
  bodies.push_back(Body(
        Vector3D(0, 0, 0),
        Vector3D(0, 0, 0),
        1.988435e30
  ));

  // earth
  const double r_e = 1.49597887e11;
  const double v_e = 29800;
  const double m_e = 5.97e24;
  bodies.push_back(Body(
        Vector3D(r_e, 0, 0),
        Vector3D(0, v_e, 0),
        m_e
  ));

  // satellite
  const double r_s = r_e + 7378140;
  const double v_s = v_e + 7350;
  const double m_s = 1e3;
  bodies.push_back(Body(
        Vector3D(r_s, 0, 0),
        Vector3D(0, v_s, 0),
        m_s
  ));

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
