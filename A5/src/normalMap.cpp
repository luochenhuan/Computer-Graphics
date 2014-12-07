#include "normalMap.hpp"

pNormalMap::pNormalMap(double scale, double amount)
{
    m_scale = scale;
    m_amount = amount;
}

Vector3D pNormalMap::modifyNormal(const InterPoint& interpt) {
   Vector3D noise;
   Point3D point = interpt.pos;
   Vector3D normal = interpt.n;
   double x = point.v_[0] * m_scale;
   double y = point.v_[1] * m_scale;
   double z = point.v_[2] * m_scale;

   noise.v_[0] = (float)(perlin.noise(x, y, z));
   noise.v_[1] = (float)(perlin.noise(y, z, x));
   noise.v_[2] = (float)(perlin.noise(z, x, y));

   Vector3D mod_n = normal + noise * m_amount;
   mod_n.normalize();
   return mod_n;
}
