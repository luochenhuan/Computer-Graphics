#ifndef CS488_LIGHT_HPP
#define CS488_LIGHT_HPP

#include "algebra.hpp"
#include <iosfwd>
#include <list>
// Represents a simple point light.
struct Light {
  Light();
  
  Colour colour;
  Point3D position;
  double falloff[3];
};

std::ostream& operator<<(std::ostream& out, const Light& l);

typedef std::list<Light*> lightList;
#endif
