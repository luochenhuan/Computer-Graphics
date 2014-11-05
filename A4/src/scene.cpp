#include "scene.hpp"
#include <iostream>


SceneNode::SceneNode(const std::string& name)
  : m_name(name)
{
}

SceneNode::~SceneNode()
{
}

void SceneNode::rotate(char axis, double angle)
{
    set_transform(m_trans*rotation(angle, axis));
}

void SceneNode::scale(const Vector3D& amount)
{
    set_transform(m_trans*scaling(amount));
}

void SceneNode::translate(const Vector3D& amount)
{
    set_transform(m_trans*translation(amount));
}


bool SceneNode::is_joint() const
{
  return false;
}

/***********************  findIntersect  **********************************/
InterPoint SceneNode::intersect(Ray ray, bool drawBx)
{
    InterPoint Interpt;

    // transform ray. Instead of moving the node, move the ray by the inverse transform
    Ray temp_ray = {m_invtrans * ray.pos, m_invtrans * ray.dir};
    // (temp_ray.dir).normalize();

    SceneNode::ChildList::const_iterator it;
    for ( it= m_children.begin(); it != m_children.end(); ++it)
    {
        SceneNode *node = *it;

        InterPoint i = node->intersect(temp_ray,drawBx);

        if (i.hit)
        {
          if (!Interpt.hit || i.t < Interpt.t)
          {
            Interpt = i;
          }
        }
    }

    // untransform the InterPoint
    if (Interpt.hit)
    {
      Interpt.pos = m_trans * Interpt.pos;
      Interpt.n = m_invtrans.transpose() * Interpt.n;
      // Interpt.n.normalize();
    }

    return Interpt;

}

InterPoint SceneNode::Sh_intersect(Ray ray, std::string nd)
{
    InterPoint Interpt;

    // transform ray. Instead of moving the node, move the ray by the inverse transform
    Ray temp_ray = {m_invtrans * ray.pos, m_invtrans * ray.dir};
    // (temp_ray.dir).normalize();

    SceneNode::ChildList::const_iterator it;
    for ( it= m_children.begin(); it != m_children.end(); ++it)
    {
        SceneNode *node = *it;
        InterPoint i = node->intersect(temp_ray, false);
        // std::cout << " shade " << std::endl;

        if (i.hit)
        {
          if (i.nd_name != nd)
          {
            Interpt = i;
            break;
          }
        }
    }

    // untransform the InterPoint
    if (Interpt.hit)
    {
      Interpt.pos = m_trans * Interpt.pos;
      Interpt.n = m_invtrans.transpose() * Interpt.n;
      // Interpt.n.normalize();
    }

    return Interpt;

}

JointNode::JointNode(const std::string& name)
  : SceneNode(name)
{
}

JointNode::~JointNode()
{
}

bool JointNode::is_joint() const
{
  return true;
}

void JointNode::set_joint_x(double min, double init, double max)
{
  m_joint_x.min = min;
  m_joint_x.init = init;
  m_joint_x.max = max;
}

void JointNode::set_joint_y(double min, double init, double max)
{
  m_joint_y.min = min;
  m_joint_y.init = init;std::cout << m_name << " finding intersect" << std::endl;
  m_joint_y.max = max;
}

GeometryNode::GeometryNode(const std::string& name, Primitive* primitive)
  : SceneNode(name),
    m_primitive(primitive)
{
}

GeometryNode::~GeometryNode()
{
}
 
/***********************  findIntersect  **********************************/
InterPoint GeometryNode::intersect(Ray ray,bool drawBx)
{
  // transform ray. Instead of moving the node, move the ray by the inverse transform
  // std::cout << m_name << " finding intersect" << std::endl;
  Ray temp_ray = {m_invtrans * ray.pos, m_invtrans * ray.dir};
  // (temp_ray.dir).normalize();

  InterPoint InterPt = m_primitive->intersect(temp_ray,drawBx);
  if (InterPt.hit)
  {
    // std::cout << name() << " intersected" << std::endl;
    InterPt.mat = m_material;
    InterPt.pos = m_trans * InterPt.pos;
    InterPt.n = m_invtrans.transpose() * InterPt.n;
    // InterPt.n.normalize();
    InterPt.nd_name = name();
  }
  else
  {
    // std::cout << name() << " not intersected" << std::endl;
  }

  return InterPt;

}
