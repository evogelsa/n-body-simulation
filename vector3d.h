#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <iostream>
#include <cmath>

class Vector3D {
  public:
    Vector3D() {}
    Vector3D(double, double, double);

    double x;
    double y;
    double z;

    double length();

    Vector3D& operator+=(const Vector3D&);
};

std::ostream& operator<<(std::ostream&, const Vector3D&);

Vector3D operator+(const Vector3D&, const Vector3D&);
Vector3D operator-(const Vector3D&, const Vector3D&);
Vector3D operator*(double, const Vector3D&);
Vector3D operator*(const Vector3D&, double);
Vector3D operator*(const Vector3D&, const Vector3D&);
Vector3D operator/(double, const Vector3D&);
Vector3D operator/(const Vector3D&, double);

#endif
