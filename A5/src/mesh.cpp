#include "mesh.hpp"
#include <iostream>

Mesh::Mesh(const std::vector<Point3D>& verts,
           const std::vector< std::vector<int> >& faces)
  : m_verts(verts),
    m_faces(faces)
{
}

Point2D Mesh::mapUV(Point3D pos)
{
    Point2D uv;
    return uv;
}

std::ostream& operator<<(std::ostream& out, const Mesh& mesh)
{
  std::cerr << "mesh({";
  for (std::vector<Point3D>::const_iterator I = mesh.m_verts.begin(); I != mesh.m_verts.end(); ++I) {
    if (I != mesh.m_verts.begin()) std::cerr << ",\n      ";
    std::cerr << *I;
  }
  std::cerr << "},\n\n     {";

  for (std::vector<Mesh::Face>::const_iterator I = mesh.m_faces.begin(); I != mesh.m_faces.end(); ++I) {
    if (I != mesh.m_faces.begin()) std::cerr << ",\n      ";
    std::cerr << "[";
    for (Mesh::Face::const_iterator J = I->begin(); J != I->end(); ++J) {
      if (J != I->begin()) std::cerr << ", ";
      std::cerr << *J;
    }
    std::cerr << "]";
  }
  std::cerr << "});" << std::endl;
  return out;
}

// Based on http://stackoverflow.com/questions/312328/what-is-the-fastest-way-to-find-the-point-of-InterPoint-between-a-ray-and-a-po
InterPoint intersectPolygon(Ray ray, std::vector<Point3D> polygon)
{
  InterPoint InterPt;

  assert(polygon.size() >= 3);
  Vector3D planeNormal = (polygon[2] - polygon[1]).cross(polygon[0] - polygon[1]);
  planeNormal.normalize();

  // ray-plane InterPoint. r = n*(V0-P0)/(n*(P1-P0))
  // p0-p1 = ray, v0 = point on plane, n plane normal

  double denom = planeNormal.dot(ray.dir);

  // if (abs(denom/ray.dir.length()) < EPSILON)
  if (denom == 0)                                       // SOOOO weird: if (denom < EPSILON) would be not right
  // ray parallel to the plane, without intersection point
  {
    return InterPt;
  }

  double nom = planeNormal.dot(polygon[0] - ray.pos);
  double t = nom/denom;
  if (t < EPSILON)
  {
	  return InterPt;
  }

  InterPt.pos = ray.pos + t*ray.dir;

  bool on_poly = false;

  for (unsigned int i = 0; i < polygon.size(); i++)
  {
	  double d = ((polygon[(i+1)%polygon.size()]) - polygon[i]).cross(InterPt.pos - polygon[i]).dot(planeNormal);
	  if (d >= 0)
	  {
		  on_poly = true;
	  }
	  else
	  {
		  on_poly = false;
		  break;
	  }

  }

  if (on_poly)
  {
    InterPt.hit = on_poly;
    InterPt.n = 1.0 * planeNormal;

    InterPt.t = t;
  }
    return InterPt;

}


BdBox Mesh::findBdBox()
{
  double Xmin = 1.0 * FAR;
  double Xmax = -1.0 * FAR;

  double Ymin = 1.0 * FAR;
  double Ymax = -1.0 * FAR;

  double Zmin = 1.0 * FAR;
  double Zmax = -1.0 * FAR;

  std::vector<Point3D>::const_iterator it;
  for (it = m_verts.begin(); it != m_verts.end(); ++it)
  {
    Xmin = (*it)[0] < Xmin ? (*it)[0] : Xmin;
    Ymin = (*it)[1] < Ymin ? (*it)[1] : Ymin;
    Zmin = (*it)[2] < Zmin ? (*it)[2] : Zmin;

    Xmax = (*it)[0] > Xmax ? (*it)[0] : Xmax;
    Ymax = (*it)[1] > Ymax ? (*it)[1] : Ymax;
    Zmax = (*it)[2] > Zmax ? (*it)[2] : Zmax;
  }

  return BdBox(Point3D(Xmin,Ymin,Zmin), Point3D(Xmax,Ymax,Zmax));
}

InterPoint Mesh::intersect(Ray ray, bool drawBx) {
  InterPoint InterPt;
  //std:cout<< m_verts.size() << " Faces: " << m_faces.size()<< std::endl;
  if (m_faces.size() < 2)
  {
    for (std::vector<Face>::const_iterator it = m_faces.begin(), end = m_faces.end(); it != end; ++it)
    {
        std::vector<Point3D> polygon;

        Face face = *it;
        for (unsigned int i = 0; i < face.size(); i++)
        {
            polygon.push_back(m_verts[face[i]]);
            //std:cout<<"\t" << face[i];
        }
        //std:cout<<polygon.size();

        InterPoint pInterPt = intersectPolygon(ray, polygon);

        if (pInterPt.hit)
        {
            if ((!InterPt.hit) || (pInterPt.t < InterPt.t) )
            {
              InterPt = pInterPt;
            }
        }
    }
    return InterPt;
  }

  BdBox bounding = findBdBox();
  bool Boxsected = bounding.IsSected(ray);
  if (!Boxsected)
  {
    // std::cout << "Mesh BdBox doesn't intersect" << std::endl;
    return InterPt;
  }

  if (!drawBx)
  // intersect ray polygon
  {
    for (std::vector<Face>::const_iterator it = m_faces.begin(), end = m_faces.end(); it != end; ++it)
    {
        std::vector<Point3D> polygon;

        Face face = *it;
        for (unsigned int i = 0; i < face.size(); i++)
        {
            polygon.push_back(m_verts[face[i]]);
            //std:cout<<"\t" << face[i];
        }
        //std:cout<<polygon.size();

        InterPoint pInterPt = intersectPolygon(ray, polygon);

        if (pInterPt.hit)
        {
            if ((!InterPt.hit) || (pInterPt.t < InterPt.t) )
            {
              InterPt = pInterPt;
            }
        }
    }
  }
  /*****************    draw BBox      ***********************/
  else
  {
      InterPt = BBoxIntersect(bounding, ray);

  }
  return InterPt;
}
