#include "material.hpp"
#include "AppWindow.hpp"

Material::~Material()
{
}

PhongMaterial::PhongMaterial(const QColor& kd, const QColor& ks, double shininess)
  : m_kd(kd), m_ks(ks), m_shininess(shininess)
{
}

PhongMaterial::~PhongMaterial()
{
}

void PhongMaterial::apply_gl(QMatrix4x4 m) const
{

//    std::cerr << "PhongMaterial" << m_ks.red() << m_ks.green() << m_ks.blue() << std::endl;
    AppWindow::m_viewer->setMaterial(m_kd,m_ks,float(m_shininess), m);
}
