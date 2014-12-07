#include "checker.hpp"

Checker::Checker(const Colour& kd, const Colour& ks, double shininess,
                double reflect_ratio, double refract_ratio, const Colour& c1, const Colour& c2, NormalMap* nm)
                : m_kd(kd), m_ks(ks), m_shininess(shininess), m_reflect_ratio(reflect_ratio), m_refract_ratio(refract_ratio), m_c1(c1), m_c2(c2)
{
    m_normalMap = nm;
}

Checker::~Checker()
{
}

Colour Checker::getColour(const Point2D& uv)
{
    unsigned char Pattern[2][2] = {{0,1},
                                   {1,0}};
    int MultiW = 5;
    int MultiH = 5;
    int X = (int) (uv.v_[0] * 2 * MultiW);
    int Y = (int) (uv.v_[1] * 2 * MultiH);
    X %= 2;
    Y %= 2;
    if (Pattern[X][Y])
        return m_c1;
    else
        return m_c2;
}
Colour Checker::getKd()
{
    return m_kd;
}
Colour Checker::getKs()
{
    return m_ks;
}
double Checker::getShininess()
{
    return m_shininess;
}
double Checker::getReflect()
{
    return m_reflect_ratio;
}
double Checker::getRefract()
{
    return m_refract_ratio;
}
