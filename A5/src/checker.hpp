#ifndef __CHECKER_HPP__
#define __CHECKER_HPP__

#include "material.hpp"

class Checker : public Material {
public:
    Checker(const Colour& kd, const Colour& ks, double shininess, double reflect_ratio, double refract_ratio,
            const Colour& c1 = Colour(1,1,1), const Colour& c2 = Colour(0,0,0), NormalMap* nm = NULL);
    virtual ~Checker();

    virtual Colour getColour(const Point2D& pos) ;
    virtual Colour getKd();
    virtual Colour getKs();
    virtual double getShininess();
    virtual double getReflect();
    virtual double getRefract();
    virtual bool is3D() {return false;}
private:
    Colour m_kd;
    Colour m_ks;
    double m_shininess;
    double m_reflect_ratio;
    double m_refract_ratio;
    Colour m_c1;
    Colour m_c2;
};

#endif
