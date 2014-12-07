#ifndef __NORMAL_MAP_HPP__
#define __NORMAL_MAP_HPP__

#include "intersection.hpp"
#include "perlinNoise.hpp"
class Primitive;
// class InterPoint;

class NormalMap {
public:
    NormalMap(){}
    virtual Vector3D modifyNormal(const InterPoint& interpt)=0;
};


class pNormalMap: public NormalMap {
private:
   PerlinNoise perlin;
   double m_scale;
   double m_amount;

public:
    pNormalMap(double scale, double amount);
    virtual Vector3D modifyNormal(const InterPoint& interpt);
};

#endif
