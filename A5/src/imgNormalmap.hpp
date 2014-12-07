#ifndef IMGNORMMAP_HPP
#define IMGNORMMAP_HPP

#include "image.hpp"
#include "material.hpp"
#include "normalMap.hpp"
#include "primitive.hpp"
// class SceneNode;

class imgNormalMap : public NormalMap{
public:
    imgNormalMap(const std::string filename);
    virtual Vector3D modifyNormal(const InterPoint& interpt);

private:
    Image m_image;
};

#endif
