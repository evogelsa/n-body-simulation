#include <cmath>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <random>
#include <sys/time.h>
#include <vector>
#include <omp.h>

#include "body.h"
#include "integration.h"
#include "vector3d.h"

int main() {
  // simulation parameters
  const double time_step = 6;
  const int max_time = 2*28*24*60*60;
  const unsigned long long max_steps = max_time / time_step;
  const int points_per_body = 1000;
  const int log_resolution = max_steps / points_per_body;

  std::vector<Body> bodies;

  // earth
  const double r_e = 0;
  const double v_e = 0;
  printf("v_e = %f\n", v_e);
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
        Vector3D(r_m + r_e, 0, 0),
        Vector3D(0, v_m, 0),
        m_m
  ));

  // // L4 lagrange point
  // const double l4_x = r_m / 2.0;
  // const double l4_y = r_m * std::sqrt(3) / 2;
  //
  // // satellite
  // const double m_s = 1e3;
  // const double v_x = -v_m * std::cos(M_PI / 6);
  // const double v_y = v_m * std::sin(M_PI / 6);
  // bodies.push_back(Body(
  //     Vector3D(l4_x, l4_y, 0),
  //     Vector3D(v_x, v_y, 0),
  //     m_s
  // ));

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
    double x, y, z;
    x = simulation.bodies[0].velocity.x;
    y = simulation.bodies[0].velocity.y;
    z = simulation.bodies[0].velocity.z;
    // print progress
    printf("\r%d / %llu (%0.1f%%) | Vel(%7.3f, %7.3f, %7.3f)", i + 1, max_steps,
           (float)(i + 1) / max_steps * 100, x, y, z);
    std::fflush(stdout);

    // compute next simulation step
    simulation.gravity_step();

    // simulation.bodies[0].position = Vector3D(0, 0, 0);
    // simulation.bodies[0].velocity = Vector3D(0, 0, 0);

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
