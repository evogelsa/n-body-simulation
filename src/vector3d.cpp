#include "vector3d.h"

Vector3D::Vector3D(double x, double y, double z) : x(x), y(y), z(z){};

double Vector3D::length() { return std::sqrt(x * x + y * y + z * z); }

Vector3D &Vector3D::operator+=(const Vector3D &other) {
  x += other.x;
  y += other.y;
  z += other.z;
  return *this;
}

std::ostream &operator<<(std::ostream &os, const Vector3D &vec) {
  os << "Vector3D(" << vec.x << ", " << vec.y << ", " << vec.z << ")";
  return os;
}

Vector3D operator+(const Vector3D &left, const Vector3D &right) {
  return Vector3D(left.x + right.x, left.y + right.y, left.z + right.z);
}

Vector3D operator-(const Vector3D &left, const Vector3D &right) {
  return Vector3D(left.x - right.x, left.y - right.y, left.z - right.z);
}

Vector3D operator*(double left, const Vector3D &right) {
  return Vector3D(left * right.x, left * right.y, left * right.z);
}

Vector3D operator*(const Vector3D &left, double right) {
  return Vector3D(left.x * right, left.y * right, left.z * right);
}

Vector3D operator*(const Vector3D &left, const Vector3D &right) {
  return Vector3D(left.x * right.x, left.y * right.y, left.z * right.z);
}

Vector3D operator/(double left, const Vector3D &right) {
  return Vector3D(left / right.x, left / right.y, left / right.z);
}

Vector3D operator/(const Vector3D &left, double right) {
  return Vector3D(left.x / right, left.y / right, left.z / right);
}
