#ifndef CS488_A4_HPP
#define CS488_A4_HPP

#include <string>
#include <thread>
#include "algebra.hpp"
#include "scene.hpp"
#include "light.hpp"
#include "EnvSetup.hpp"
#include "image.hpp"

void a4_render(// What to render
               SceneNode* root,
               // Where to output the image
               const std::string& filename,
               // Image size
               const int width, const int height,
               // Viewing parameters
               const Point3D& eye, const Vector3D& view,
               const Vector3D& up, double fov,
               // Lighting parameters
               const Colour& ambient,
               const std::list<Light*>& lights
               );

void Trace_ray(int start_line, int line_num, const Env& root_scene, Image& img);
void Trace_ray_aa(int x_ori, int y_ori, const Env& root_scene, Image& img);

Colour castRay(SceneNode* root, Ray r, const Colour& ambient,
                      const std::list<Light*>& lights, int level, int x, int y);

Colour performLighting(SceneNode* root, Ray r, const InterPoint& closest_interpt,
                      const Colour& ambient, const std::list<Light*>& lights, int level, int x, int y);

Colour getDiffuseAndSpecularLighting(SceneNode* root, Ray ray, const InterPoint& interpt,
                      const std::list<Light*>& lights);

Colour getReflectiveRefractiveLighting(SceneNode* root, Ray ray, const InterPoint& intersection,
                      const Colour& ambient, const std::list<Light*>& lights, int level, int x, int y);

Ray Reflect(Ray ray, InterPoint closest_interpt);
Ray Refract(Ray ray, InterPoint closest_interpt, double m_refract_ratio);
double getReflectance(Ray ray, const InterPoint& intersection, double m_refract_ratio);

bool Shadowed(const InterPoint& closest_interpt, SceneNode* node, const Point3D& light_pos);
Colour background(int x, int y);

bool isInternalRefl(Ray ray, InterPoint closest_interpt, double m_refract_ratio);
#endif
