#ifndef CS488_MESH_HPP
#define CS488_MESH_HPP

#include <vector>
#include <iosfwd>
#include <cassert>
#include "primitive.hpp"
#include "algebra.hpp"

// A polygonal mesh.
class Mesh : public Primitive {
public:
  Mesh(const std::vector<Point3D>& verts,
       const std::vector< std::vector<int> >& faces);

  typedef std::vector<int> Face;
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);
  virtual Point2D mapUV(Point3D pos);

private:
  std::vector<Point3D> m_verts;
  std::vector<Face> m_faces;

  friend std::ostream& operator<<(std::ostream& out, const Mesh& mesh);
};

#endif
