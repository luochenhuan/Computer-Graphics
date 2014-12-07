#ifndef INTERSECTION_HPP
#define INTERSECTION_HPP

#include <string>
#include "algebra.hpp"
class SceneNode;

class InterPoint {
public:
  SceneNode* obj;
  double t; 		// distance along ray to InterPoint
  Point3D pos;     	// location of intersection
  Point2D uv;
  Vector3D n;  		// normal for this InterPoint surface
  bool hit;
  InterPoint():obj(NULL), t(-1.0), hit(false)
  {
  }
  // Colour getColour(Point2D uv) const;
};
#endif
