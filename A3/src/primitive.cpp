#include "primitive.hpp"
#include "AppWindow.hpp"

Primitive::~Primitive()
{
}

Sphere::~Sphere()
{
}

void Sphere::walk_gl(bool picking, QMatrix4x4 m, float r, float g, float b, bool pick) const
{
  // Fill me in
    if (picking)
    {
//        std::cerr << "picking: " << r << std::endl;
        AppWindow::m_viewer->set_colour(r,g,b);
        AppWindow::m_viewer->draw_sphere(m);
    }
    else
    {
        if (pick==true){
            std::cerr << "sphere : set pure color " << r<< " " << g << " " <<std::endl;
            AppWindow::m_viewer->set_colour(1.0,0.5,0.5);
            AppWindow::m_viewer->draw_sphere(m);
        }
        else
            AppWindow::m_viewer->draw_sphere(m);
    }
}
