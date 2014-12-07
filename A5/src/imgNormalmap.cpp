#include "imgNormalmap.hpp"
#include "scene.hpp"

imgNormalMap::imgNormalMap(const std::string filename)
{
    if (!m_image.loadPng(filename))
    {
        std::cerr << "Failed to load texture " << filename << std::endl;
        exit(-1);
    }
}


// Map [u,v] of range [0,1] to [width, height]
// Does bilinear interpolation.  Also clamps
Vector3D imgNormalMap::modifyNormal(const InterPoint& interpt) {

    // std::cout << interpt.obj -> name() << " mapUV" << std::endl;
    Point2D uv = interpt.uv; 
    // std::cout << interpt.obj -> name() << " mapUV done" << std::endl;
    const int width = m_image.width();
    const int height = m_image.height();

    // clamp u,v to [0,1]. Interpolate between two points
    int umin = int(width  * uv.v_[0]);
    int vmin = int(height * uv.v_[1]);

    umin = std::min(std::max(umin, 0), width -1);
    vmin = std::min(std::max(vmin, 0), height-1);

    // 4 samples on square
    Colour c0 = m_image(umin, vmin);
    double x = 2 * c0.R() -1;
    double y = 2 * c0.G() -1;
    double z = 2 * c0.B() -1;
    Vector3D norm = Vector3D(x, y, z);
    norm.normalize();
    return norm;
}
