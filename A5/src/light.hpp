#ifndef CS488_LIGHT_HPP
#define CS488_LIGHT_HPP

#include "algebra.hpp"
#include "colour.hpp"
#include <iosfwd>
#include <list>
// Represents a simple point light.
class Light {
public:
    Point3D position;
    Colour colour;
    double falloff[3];
    Light();
    Light(Point3D pos, Colour c, double f0 = 1, double f1 = 0, double f2 = 0):
        position(pos),
        colour(c)
    {
        falloff[0] = f0;
        falloff[1] = f1;
        falloff[2] = f2;
    };
    virtual float LightFactor(const Vector3D& L) {return 1.0;}
    virtual bool isArea(){return false;}
};

std::ostream& operator<<(std::ostream& out, const Light& l);

typedef std::list<Light*> lightList;


class DirectedLight: public Light {
public:
    Vector3D direction;
    int  DirPow;
    DirectedLight(Point3D pos, Colour c, double f0 = 1, double f1 = 0, double f2 = 0,
                  Vector3D dir = Vector3D(0,0,-1), int Pow = 10):
    Light(pos, c, f0, f1, f2)

    {
        direction = dir,
        DirPow = Pow;
    };

    void setDirection(Vector3D Dir);

    virtual float LightFactor(const Vector3D& L)
    {
        float cosRadian = -1.0 * L.dot(direction)/(L.length() * direction.length());
        if (cosRadian > 0)
            return pow(cosRadian, DirPow);
        return 0;
    }
};

class ConeLight: public Light {
public:
    Vector3D direction;
    int  DirPow;
    float HalfCos;
    ConeLight(Point3D pos, Colour c, double f0 = 1, double f1 = 0, double f2 = 0,
                  Vector3D dir = Vector3D(0,0,-1), int Pow = 10, float gamma = 0.9397):
    Light(pos, c, f0, f1, f2)
    {
        direction = dir,
        DirPow = Pow;
        HalfCos = gamma;
    };

    virtual float LightFactor(const Vector3D& L)
    {
        float cosRadian = -1.0 * L.dot(direction)/(L.length() * direction.length());
        if (cosRadian > 0 && cosRadian >= HalfCos)
            return pow(cosRadian, DirPow);
        return 0;
    }

    void setConeAngle(float Angle);
};

std::ostream& operator<<(std::ostream& out, const ConeLight& l);


class AreaLight: public Light {
public:
    Point3D position;
    Colour colour;
    double falloff[3];
    Vector3D m_v1;
    Vector3D m_v2;
    double m_width;
    double m_height;
    AreaLight(Point3D pos, Colour c, double f0 = 1, double f1 = 0, double f2 = 0,
              Vector3D v1=Vector3D(1,0,0), Vector3D v2=Vector3D(0,1,0), double width=1, double height=1):
            position(pos),colour(c),
            m_v1(v1), m_v2(v2), m_width(width), m_height(height)
    {
        falloff[0] = f0;
        falloff[1] = f1;
        falloff[2] = f2;
        m_v1.normalize();
        m_v2.normalize();
    };
    virtual float LightFactor(const Vector3D& L) {return 1.0;}
    virtual bool isArea(){return true;}
};

#endif
