#include <cstdio>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>

#include "body.h"
#include "integration.h"
#include "vector3d.h"

int main() {
  const double time_step = 60;
  const int max_time = 365*24*60*60;
  const unsigned long long max_steps = max_time / time_step;
  const int points_per_body = 1000;
  const int log_resolution = max_steps / points_per_body;

  std::vector<Body> bodies;

  // earth
  const double r_e = 0;
  const double v_e = 0;
  const double m_e = 5.97e24;
  bodies.push_back(Body(
        Vector3D(r_e, 0, 0),
        Vector3D(0, v_e, 0),
        m_e
  ));

  // moon
  const double r_m = 3.844e8;
  const double v_m = 1020;
  const double m_m = 7.3459e22;
  bodies.push_back(Body(
        Vector3D(r_m, 0, 0),
        Vector3D(0, v_m, 0),
        m_m
  ));

  // satellite
  const double m_s = 1e3;
  bodies.push_back(Body(
        Vector3D(-333326298.9295349, 19007567.817135274, -271161377.07902527),
        Vector3D(790.6644000361339, -17.607214696246114, -1093.2669313970146),
        m_s
  ));
  // const double m_s = 1e3;
  // bodies.push_back(Body(
  //       Vector3D(363014796.06842, -9643291.06731, 1032449.86122),
  //       Vector3D(885.94768, -825.10859, -82.91827),
  //       m_s
  // ));

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
