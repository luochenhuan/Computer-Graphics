#include "imgTexture.hpp"


imgTexture::imgTexture(const std::string filename, const Colour& kd, const Colour& ks, double shininess, double reflect_ratio, double refract_ratio,
                        NormalMap* nm):
                        m_kd(kd), m_ks(ks), m_shininess(shininess), m_reflect_ratio(reflect_ratio), m_refract_ratio(refract_ratio)
{
    if (!m_image.loadPng(filename))
        {
            std::cerr << "Failed to load texture " << filename << std::endl;
            exit(-1);
        }
    m_normalMap = nm;
}

imgTexture::~imgTexture()
{
}

// Map [u,v] of range [0,1] to [width, height]
// Does bilinear interpolation.  Also clamps
Colour imgTexture::getColour(const Point2D& uv)
{
    const int width = m_image.width();
    const int height = m_image.height();
    //
    //	u = abs(u);
    //	v = abs(v);

    // clamp u,v to [0,1]. Interpolate between two points
    int umin = int(width  * uv.v_[0]);
    int umax = int(width  * uv.v_[0]) + 1;
    int vmin = int(height * uv.v_[1]);
    int vmax = int(height * uv.v_[1]) + 1;

    umin = std::min(std::max(umin, 0), width -1 );
    umax = std::min(std::max(umax, 0), width -1 );
    vmin = std::min(std::max(vmin, 0), height-1);
    vmax = std::min(std::max(vmax, 0), height - 1);

    // 4 samples on square
    Colour p0 = m_image(umin, vmin);
    Colour p1 = m_image(umin, vmax);
    Colour p2 = m_image(umax, vmin);
    Colour p3 = m_image(umax, vmax);

    double uD = width * uv.v_[0] - umin;
    double vD = height* uv.v_[1] - vmin;

    //4 point interpolation
    Colour finalColour = vD * (uD * p0 + (1.0 - uD) * p1) +	// top points
                        (1.0 - vD) * (uD * p2 + (1.0 - uD) * p3);//bottom points

    return finalColour;

}
Colour imgTexture::getKd()
{
    return m_kd;
}
Colour imgTexture::getKs()
{
    return m_ks;
}
double imgTexture::getShininess()
{
    return m_shininess;
}
double imgTexture::getReflect()
{
    return m_reflect_ratio;
}
double imgTexture::getRefract()
{
    return m_refract_ratio;
}
