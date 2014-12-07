#ifndef IMGTEXTURE_HPP
#define IMGTEXTURE_HPP

#include "image.hpp"
#include "material.hpp"


class imgTexture : public Material{
public:
    imgTexture(const std::string filename, const Colour& kd, const Colour& ks, double shininess, double reflect_ratio, double refract_ratio,
                NormalMap* nm = NULL);
    virtual ~imgTexture();

    virtual Colour getColour(const Point2D& pos) ;
    virtual Colour getKd();
    virtual Colour getKs();
    virtual double getShininess();
    virtual double getReflect();
    virtual double getRefract();
    virtual bool is3D() {return false;}

private:
    Image m_image;
    Colour m_kd;
    Colour m_ks;
    double m_shininess;
    double m_reflect_ratio;
    double m_refract_ratio;
};

#endif
