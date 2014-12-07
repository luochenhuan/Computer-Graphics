#include "material.hpp"

Material::~Material()
{
}

Colour Material::getColour(const Point2D& pos)
{
    return Colour(0,0,0);
}

Colour Material::getColour(const Point3D& pos)
{
    return Colour(0,0,0);
}

Vector3D Material::modifyNormal(const InterPoint& interpt)
{
    if (m_normalMap != NULL)
    {
        return m_normalMap->modifyNormal(interpt);
    }
    else
    {
        return interpt.n;
    }
}
/*
Colour Material::getKd()
{
    return Colour(0,0,0);
}
Colour Material::getKs()
{
    return Colour(0,0,0);
}
double Material::getShininess()
{
    return 0;
}
double Material::getReflect()
{
    return 0;
}
double Material::getRefract()
{
    return 0;
}
*/

PhongMaterial::PhongMaterial(const Colour& kd, const Colour& ks, double shininess, double reflect_ratio, double refract_ratio, NormalMap* nm)
  : m_kd(kd), m_ks(ks), m_shininess(shininess), m_reflect_ratio(reflect_ratio), m_refract_ratio(refract_ratio)
{
    m_normalMap = nm;
}

PhongMaterial::~PhongMaterial()
{
}

Colour PhongMaterial::getColour(const Point2D& pos)
{
    return Colour(0,0,0);
}
Colour PhongMaterial::getKd()
{
    return m_kd;
}
Colour PhongMaterial::getKs()
{
    return m_ks;
}
double PhongMaterial::getShininess()
{
    return m_shininess;
}
double PhongMaterial::getReflect()
{
    return m_reflect_ratio;
}
double PhongMaterial::getRefract()
{
    return m_refract_ratio;
}
//void PhongMaterial::apply_gl() const
//{
//  // Perform OpenGL calls necessary to set up this material.
//}
