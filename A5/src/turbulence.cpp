#include "turbulence.hpp"

Turbulence::Turbulence(const Colour& kd, const Colour& ks, double shininess, double reflect_ratio,
                                double refract_ratio, int scale, int level, const Colour& c1, const Colour& c2):
                                m_kd(kd), m_ks(ks), m_shininess(shininess), m_reflect_ratio(reflect_ratio),
                                m_refract_ratio(refract_ratio), m_scale(scale), m_level(level), m_c1(c1), m_c2(c2)
{
}

Turbulence::~Turbulence()
{
}

Colour Turbulence::getColour(const Point3D& p) {
   double x = p.v_[0] * m_scale;
   double y = p.v_[1] * m_scale;
   double z = p.v_[2] * m_scale;
   double noiseCoef = 0;

   for (int level = 1; level < m_level; level++) {
      noiseCoef += (1.0f / m_level) * fabsf(perlin.noise(
         level * 0.05 * x,
         level * 0.15 * y,
         level * 0.05 * z
      ));
   }
   noiseCoef = 0.5 * sinf((x+y)*0.05 + noiseCoef) + 0.5;
   return m_c1 * noiseCoef + (1.0f - noiseCoef) * m_c2;
}

Colour Turbulence::getKd()
{
    return m_kd;
}
Colour Turbulence::getKs()
{
    return m_ks;
}
double Turbulence::getShininess()
{
    return m_shininess;
}
double Turbulence::getReflect()
{
    return m_reflect_ratio;
}
double Turbulence::getRefract()
{
    return m_refract_ratio;
}
