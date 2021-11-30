#include "integration.h"

const double G = 6.674e-11;

RK4::RK4(std::vector<Body> bodies, double time_step)
    : bodies(bodies), time_step(time_step){};

Vector3D RK4::single_body_accel(int index) {
  Vector3D accel = Vector3D(0, 0, 0);
  Vector3D vel_update = Vector3D(0, 0, 0);
  Vector3D pos_update = Vector3D(0, 0, 0);
  Body target_body = bodies[index];

  int i = 0;
  for (auto other = bodies.begin(); other != bodies.end(); *other++, i++) {
    if (i != index) {
      Vector3D k1 = Vector3D(0, 0, 0);
      Vector3D k2 = Vector3D(0, 0, 0);
      Vector3D k3 = Vector3D(0, 0, 0);
      Vector3D k4 = Vector3D(0, 0, 0);

      // double r = (std::pow((target_body.position.x - other->position.x), 2)
      //             + std::pow((target_body.position.y - other->position.y), 2)
      //             + std::pow((target_body.position.z - other->position.z),
      //             2));
      //
      // r = std::sqrt(r);

      double r = (target_body.position - other->position).length();

      double tmp = G * other->mass / (r * r * r);

      k1 = (other->position - target_body.position) * tmp;

      vel_update = partial_step(target_body.velocity, k1, 0.5);
      pos_update = partial_step(target_body.position, vel_update, 0.5);
      k2 = (other->position - pos_update) * tmp;

      vel_update = partial_step(target_body.velocity, k2, 0.5);
      pos_update = partial_step(target_body.position, vel_update, 0.5);
      k3 = (other->position - pos_update) * tmp;

      vel_update = partial_step(target_body.velocity, k3, 1);
      pos_update = partial_step(target_body.position, vel_update, 1);
      k4 = (other->position - pos_update) * tmp;

      accel += (k1 + k2 * 2 + k3 * 2 + k4) / 6;
    }
  }

  return accel;
}

Vector3D RK4::partial_step(Vector3D &f, Vector3D &df, double scale) {
  return Vector3D(f.x + df.x * time_step * scale,
                  f.y + df.y * time_step * scale,
                  f.z + df.z * time_step * scale);
}

void RK4::update_velocity() {
  int i;
#pragma omp parallel for schedule(dynamic) private(i) shared(bodies, time_step)
  for (i = 0; i < bodies.size(); i++) {
    Vector3D accel = RK4::single_body_accel(i);
    bodies[i].velocity += accel * time_step;
  }
}

void RK4::update_position() {
  for (auto body = bodies.begin(); body != bodies.end(); *body++) {
    body->position += body->velocity * time_step;
  }
}

void RK4::gravity_step() {
  update_velocity();
  update_position();
}

void RK4::log_state(std::ofstream &ofs) {
  int i = 0;
  for (auto body = bodies.begin(); body != bodies.end(); *body++, i++) {
    ofs << i << "," << body->position.x << "," << body->position.y << ","
        << body->position.z << std::endl;
  }
}
