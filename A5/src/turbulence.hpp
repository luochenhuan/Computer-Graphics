#ifndef __TURBULENCE_HPP__
#define __TURBULENCE_HPP__

/**
** ref:https://github.com/marczych/RayTracer
**/

#include "material.hpp"
#include "perlinNoise.hpp"

class Turbulence : public Material {
public:
    Turbulence(const Colour& kd, const Colour& ks, double shininess, double reflect_ratio, double refract_ratio,
               int scale, int level, const Colour& c1 = Colour(1,1,1), const Colour& c2 = Colour(0,0,0));
    virtual ~Turbulence();

    virtual Colour getColour(const Point3D& pos) ;
    virtual Colour getKd();
    virtual Colour getKs();
    virtual double getShininess();
    virtual double getReflect();
    virtual double getRefract();
    virtual bool   is3D(){return true;}

private:
    Colour m_kd;
    Colour m_ks;
    double m_shininess;
    double m_reflect_ratio;
    double m_refract_ratio;
    int m_scale;
    int m_level;
    Colour m_c1;
    Colour m_c2;
    PerlinNoise perlin;
};

#endif
