#include "algebra.hpp"

struct ImgPlane
{
  int width;
  int height;
  double pixelHeight;
  double pixelWidth;

  ImgPlane (int w, int h, double ph, double pw):
            width(w), height(h), pixelHeight(ph),pixelWidth(pw){}
};

class Env
{
public:
// Constructor
    Env(SceneNode *root,
        const Point3D& eye,
        const Vector3D& dir,
        const Vector3D& right,
        const Vector3D& up,
        double fov,
        const Colour& ambient,
        const std::list<Light*> lights,
        ImgPlane& plane):
      root(root),
      eye(eye),
      dir(dir),
      right(right),
      up(up),
      fov(fov),
      ambient(ambient),
      lights(lights),
      plane(plane)
    { }

    const Point3D get_eye() const { return eye; };

    double get_fov() const { return fov; };

    const Vector3D get_dir() const { return dir; };

    SceneNode*      root;    
    const Point3D&  eye;
    const Vector3D& dir;
    const Vector3D& right;
    const Vector3D& up;
    double fov;
    const Colour& ambient;
    std::list<Light*> lights;
    ImgPlane plane;

};