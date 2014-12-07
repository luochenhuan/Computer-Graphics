#ifndef CS488_A4_HPP
#define CS488_A4_HPP

#include <string>
#include "algebra.hpp"
#include "scene.hpp"
#include "light.hpp"

void a4_render(// What to render
               SceneNode* root,
               // Where to output the image
               const std::string& filename,
               // Image size
               int width, int height,
               // Viewing parameters
               const Point3D& eye, const Vector3D& view,
               const Vector3D& up, double fov,
               // Lighting parameters
               const Colour& ambient,
               const std::list<Light*>& lights
               );

Colour ray_tracing (const Ray ray, SceneNode* node, const Light* light, 
                    const Colour& ambient, int level, bool& intersected);

Colour shading(const Ray ray, InterPoint interpt, const Light* light);
               

bool Shadowed(InterPoint closest_interpt, SceneNode* node, const Light* light);

#endif
