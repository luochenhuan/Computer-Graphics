#ifndef __PERLIN_NOISE_HPP__
#define __PERLIN_NOISE_HPP__
#include "algebra.hpp"
/**
 * Ref: https://github.com/marczych/RayTracer
 */
class PerlinNoise {
private:
   int p[512];

   double fade(double t);
   double lerp(double t, double a, double b);
   double grad(int hash, double x, double y, double z);

public:
   PerlinNoise();

   double noise(double x, double y, double z);
};

#endif
