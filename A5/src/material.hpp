#ifndef CS488_MATERIAL_HPP
#define CS488_MATERIAL_HPP

#include "algebra.hpp"
#include "colour.hpp"
#include "normalMap.hpp"
#include "imgNormalmap.hpp"
#include "intersection.hpp"

class Material {
public:
  Material()
  {
      m_normalMap = NULL;
  }
  virtual ~Material();
  virtual Colour getColour(const Point3D& pos);
  virtual Colour getColour(const Point2D& pos);
  virtual Colour getKd() = 0;
  virtual Colour getKs() = 0;
  virtual double getShininess() = 0;
  virtual double getReflect() = 0;
  virtual double getRefract() = 0;
  virtual bool is3D() = 0; // to determine if obj needs to convert to UV coordinates
  Vector3D modifyNormal(const InterPoint& interpt);
protected:
  NormalMap* m_normalMap;
};


class PhongMaterial : public Material {
public:
  PhongMaterial(const Colour& kd, const Colour& ks, double shininess, double reflect_ratio, double refract_ratio, NormalMap* nm = NULL);
  virtual ~PhongMaterial();

  virtual Colour getColour(const Point2D& pos);
  virtual Colour getKd();
  virtual Colour getKs();
  virtual double getShininess();
  virtual double getReflect();
  virtual double getRefract();
  virtual bool is3D() {return true;}
private:
  Colour m_kd;
  Colour m_ks;
  double m_shininess;
  double m_reflect_ratio;
  double m_refract_ratio;
};


#endif
