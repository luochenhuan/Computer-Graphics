#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"

class Mesh;

class BdBox{
public:
  BdBox(const Point3D& minP,const Point3D& maxP)
        :m_minP(minP), m_maxP(maxP)
        {}

  bool IsSected(Ray ray);

  Point3D m_minP, m_maxP;
};

class Primitive {
public:
  virtual ~Primitive();
  virtual BdBox findBdBox() = 0;
  virtual InterPoint intersect(Ray ray, bool drawBx) = 0;

};


class NonhierSphere : public Primitive {
public:
  NonhierSphere(const Point3D& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
  }
  virtual ~NonhierSphere();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);


private:
  Point3D m_pos;
  double m_radius;
};

// Box is really a mesh
class NonhierBox : public Primitive {
public:
  NonhierBox(const Point3D& pos, double size);
  
  virtual ~NonhierBox();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);


private:
  Point3D m_pos;
  double m_size;
  Mesh *m_mesh;
};

class Sphere : public Primitive {
public:
  Sphere();
  virtual ~Sphere();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);
private:
  NonhierSphere *m_sphere;
};

class Cube : public Primitive {
public:
  Cube();
  virtual ~Cube();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);
private:
  NonhierBox *m_cube;
};


#endif

