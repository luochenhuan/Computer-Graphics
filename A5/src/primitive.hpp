#ifndef CS488_PRIMITIVE_HPP
#define CS488_PRIMITIVE_HPP

#include "algebra.hpp"
#include "intersection.hpp"
#include "boundBox.hpp"
class Mesh;

InterPoint BBoxIntersect(BdBox bounding, Ray ray);
/******************************  Primitive  *******************************************/
class Primitive {
public:
  Primitive() {}
  virtual ~Primitive();
  virtual BdBox findBdBox() = 0;
  virtual InterPoint intersect(Ray ray, bool drawBx) = 0;
  virtual Point2D mapUV(Point3D pos) = 0;
protected:
  BdBox m_BdBox;
};

/******************************  Sphere  *******************************************/
class NonhierSphere : public Primitive {
public:
  NonhierSphere(const Point3D& pos, double radius)
    : m_pos(pos), m_radius(radius)
  {
    //   m_BdBox = findBdBox();
  }
  virtual ~NonhierSphere();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);
  virtual Point2D mapUV(Point3D pos);
private:
  Point3D m_pos;
  double m_radius;
};

/******************************  Cylinder  *******************************************/
class NonhierCylinder : public Primitive {
public:
  NonhierCylinder(const Point3D& pos, const Vector3D& ori, double radius,double height)
    : m_pos(pos), m_ori(ori), m_radius(radius), m_height(height)
  {
    //   m_BdBox = findBdBox();
    m_ori.normalize();
  }
  virtual ~NonhierCylinder();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);
  virtual Point2D mapUV(Point3D pos);

private:
  Point3D m_pos;
  Vector3D m_ori;
  double m_radius;
  double m_height;
};

/******************************  Cone  *******************************************/
class NonhierCone : public Primitive {
public:
  NonhierCone(const Point3D& pos, double radius, double height, double yend)
    : m_pos(pos), m_radius(radius), m_height(height), m_yend(yend)
  {
    //   m_BdBox = findBdBox();
  }
  virtual ~NonhierCone();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);
  virtual Point2D mapUV(Point3D pos);

private:
  Point3D m_pos;
  double m_radius;
  double m_height;
  double m_yend;
};

/******************************  Plane  *******************************************/
class Plane : public Primitive {
public:
  Plane(const Point3D& pos, const Vector3D& v1, const Vector3D& v2, double width,double height)
    : m_pos(pos), m_v1(v1), m_v2(v2), m_width(width), m_height(height)
  {
    m_norm = m_v1.cross(m_v2);
    m_norm.normalize();
    // m_BdBox = findBdBox();
  }
  virtual ~Plane();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);
  virtual Point2D mapUV(Point3D pos);

private:
  Point3D m_pos;
  Vector3D m_v1;
  Vector3D m_v2;
  Vector3D m_norm;
  double m_width;
  double m_height;
};

/******************************  NonhierBox  *******************************************/
// Box is a mesh actually
class NonhierBox : public Primitive {
public:
  NonhierBox(const Point3D& pos, double size);

  virtual ~NonhierBox();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);
  virtual Point2D mapUV(Point3D pos);

private:
  Point3D m_pos;
  double m_size;
  Mesh *m_mesh;
};

/******************************  Cuboid  *******************************************/
// Box is a mesh actually
class Cuboid : public Primitive {
public:
    Cuboid(const Point3D& pos, double width, double height, double depth);

  virtual ~Cuboid();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);
  virtual Point2D mapUV(Point3D pos);

private:
  Point3D m_pos;
  double m_width;
  double m_height;
  double m_depth;
  Mesh *m_mesh;
};
/******************************  Sphere  *******************************************/
class Sphere : public Primitive {
public:
  Sphere();
  virtual ~Sphere();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);
  virtual Point2D mapUV(Point3D pos);

private:
  NonhierSphere *m_sphere;
};

/******************************  Cube  *******************************************/
class Cube : public Primitive {
public:
  Cube();
  virtual ~Cube();
  virtual BdBox findBdBox();
  virtual InterPoint intersect(Ray ray, bool drawBx);
  virtual Point2D mapUV(Point3D pos);

private:
  NonhierBox *m_cube;
};


#endif
