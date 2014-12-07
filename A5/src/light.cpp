#include "light.hpp"
#include <iostream>


Light::Light()
  : position(0.0, 0.0, 0.0),
    colour(0.0, 0.0, 0.0)
{
  falloff[0] = 1.0;
  falloff[1] = 0.0;
  falloff[2] = 0.0;
}

std::ostream& operator<<(std::ostream& out, const Light& l)
{
  out << "L[" << l.colour << ", " << l.position << ", ";
  for (int i = 0; i < 3; i++) {
    if (i > 0) out << ", ";
    out << l.falloff[i];
  }
  out << "]";
  return out;
}


void DirectedLight::setDirection(Vector3D Dir)
{
  direction = Dir;
}

void ConeLight::setConeAngle(float Angle)
{
  HalfCos = Angle;
}

std::ostream& operator<<(std::ostream& out, const ConeLight& l)
{
  out << "ConeL[" << l.colour << ", " << l.position << ", ";
  for (int i = 0; i < 3; i++) {
    if (i > 0) out << ", ";
    out << l.falloff[i];
  }
  out << ", ";
  out << l.direction << ", ";
  out << l.HalfCos;
  out << "]";

  return out;
}
