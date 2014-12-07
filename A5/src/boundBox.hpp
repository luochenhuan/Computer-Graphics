#ifndef BOUNDBOX_HPP
#define BOUNDBOX_HPP

#include "algebra.hpp"
/******************************  Bounding Box  *****************************************/
class BdBox{
public:
  BdBox()
  {
      m_minP = Point3D(FAR, FAR, FAR);
      m_maxP = Point3D(-FAR, -FAR, -FAR);
  }
  BdBox(const Point3D& minP,const Point3D& maxP)
        :m_minP(minP), m_maxP(maxP)
        {}

  bool IsSected(Ray ray);

  Point3D m_minP;
  Point3D m_maxP;
};

#endif
