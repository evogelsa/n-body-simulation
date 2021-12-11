#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <random>
#include <sys/time.h>
#include <vector>

#include "body.h"
#include "integration.h"
#include "vector3d.h"

int main() {
  // simulation parameters
  const double time_step = 1;
  const int max_time = 1000;
  const unsigned long long max_steps = max_time / time_step;
  const int points_per_body = 1000;
  const int log_resolution = max_steps / points_per_body;

  // vector to hold each body
  std::vector<Body> bodies;

  // randomly generate initial conditions for each body
  std::default_random_engine generator;
  std::uniform_real_distribution<double> distribution(-1.0, 1.0);

  // create each body with initial conditions and add to vector
  int nbodies = 1000;
  for (int i = 0; i < nbodies; i++) {
    double x = distribution(generator) * 2;
    double y = distribution(generator) * 2;
    double z = distribution(generator) * 2;
    double vx = distribution(generator) * 1e-3;
    double vy = distribution(generator) * 1e-3;
    double vz = distribution(generator) * 1e-3;
    double m = 1e5;

    bodies.push_back(Body(Vector3D(x, y, z), Vector3D(vx, vy, vz), m));
  }

  // create an output file
  std::ofstream output("output.csv", std::ios::out);

  // create a simulation instance
  RK4 simulation(bodies, time_step);

  // measure time to complete simulation
  struct timeval t0, t1;
  double elapsed = 0;

  gettimeofday(&t0, NULL);

  // simulate for determined number of steps
  for (int i = 0; i < max_steps; i++) {
    // print progress
    printf("\r%d / %llu (%0.1f%%)", i + 1, max_steps,
           (float)(i + 1) / max_steps * 100);
    std::fflush(stdout);

    // compute next simulation step
    simulation.gravity_step();

    // log at the desired resolution (snapshot of sim taken every x steps)
    if (i % log_resolution == 0)
      simulation.log_state(output);
  }
  printf("\n");

  gettimeofday(&t1, NULL);

  elapsed = (t1.tv_sec - t0.tv_sec) + (t1.tv_usec - t0.tv_usec) / 1e6;

  printf("Elapsed time: %fs\n", elapsed);

  return 0;
}
