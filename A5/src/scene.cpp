#include "scene.hpp"
#include <iostream>


SceneNode::SceneNode(const std::string& name)
  : m_name(name)
{
    m_BdBox = BdBox( Point3D(FAR, FAR, FAR), Point3D(-FAR, -FAR, -FAR));
    m_isWalked = false;
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

BdBox SceneNode::get_BdBox()
{
    // Point3D minP = m_BdBox.m_minP;
    // Point3D maxP = m_BdBox.m_maxP;
    //
    // minP = m_trans * minP;
    // maxP = m_trans * maxP;

    return m_BdBox;
}

BdBox SceneNode::walk_gl()
{
    BdBox maxBB = get_BdBox();

    // already searched
    if (m_isWalked)
        return m_BdBox;

    SceneNode::ChildList::const_iterator it;
    for ( it= m_children.begin(); it != m_children.end(); ++it)
    {
        BdBox curBB = (*it)->walk_gl();

        curBB.m_minP= m_trans * maxBB.m_minP;
        curBB.m_maxP= m_trans * maxBB.m_maxP;

        maxBB.m_minP = Point3D(std::min(maxBB.m_minP.v_[0], curBB.m_minP.v_[0]),
                               std::min(maxBB.m_minP.v_[1], curBB.m_minP.v_[1]),
                               std::min(maxBB.m_minP.v_[2], curBB.m_minP.v_[2]));

        maxBB.m_maxP = Point3D(std::max(maxBB.m_maxP.v_[0], curBB.m_maxP.v_[0]),
                               std::max(maxBB.m_maxP.v_[1], curBB.m_maxP.v_[1]),
                               std::max(maxBB.m_maxP.v_[2], curBB.m_maxP.v_[2]));
    }

    m_isWalked = true;
    m_BdBox = maxBB;


    // std::cerr << "SceneNode "<< name() << " bbox: minP( " << m_BdBox.m_minP << ")" << " maxP( " << m_BdBox.m_maxP << ")" << std::endl;

    return m_BdBox;
}

/***********************  findIntersect  **********************************/
InterPoint SceneNode::intersect(Ray ray, bool drawBx, int layer)
{
    InterPoint Interpt;
    // std::cerr << "ray.dir: "<< ray.dir << std::endl;

    // transform ray. Instead of moving the node, move the ray by the inverse transform
    Ray temp_ray = {m_invtrans * ray.pos, m_invtrans * ray.dir};

    bool bbSected = m_BdBox.IsSected(temp_ray);

    if (!bbSected){
        // std::cerr << "SceneNode "<< name() << " BBox doesn't intersect with ray; layer: " << layer << std::endl;
        return Interpt;
    }

    if (drawBx && layer >= DRAWHIER)
    {
        // std::cerr << "SceneNode "<< name() << " BBox Mesh intersection; layer: " << layer << std::endl;
        Interpt = BBoxIntersect(m_BdBox, ray);
        Interpt.obj = this;
        // Interpt.pos = m_trans * Interpt.pos;
        // Interpt.n = m_invtrans.transpose() * Interpt.n;
        return Interpt;
    }


    SceneNode::ChildList::const_iterator it;
    for ( it= m_children.begin(); it != m_children.end(); ++it)
    {
        SceneNode *node = *it;

        InterPoint i = node->intersect(temp_ray, drawBx, layer + 1);

        if (i.hit)
        {
          if (!Interpt.hit || i.t < Interpt.t)
          {
            Interpt = i;
          }
        }
    }

    // std::cerr << "Interpt.hit " << Interpt.hit << std::endl;
    // untransform the InterPoint
    if (Interpt.hit)
    {
        // std::cerr << "Interpt.hit "<< Interpt.obj->name() << "  layer: " << layer << std::endl;
        // std::cerr << "Interpt.pos "<< std::endl;
        Interpt.pos = m_trans * Interpt.pos;
        // std::cerr << "Interpt.n "<< Interpt.n << std::endl;
        Interpt.n = m_invtrans.transpose() * Interpt.n;
        // std::cerr << "Interpt.n transformed "<< Interpt.n << std::endl;
        
        // if (Interpt.obj->name() == "s1")
        //     std::cout << "s1 intersect cos" <<  ray.dir.dot (Interpt.n) / (ray.dir.length()*Interpt.n.length()) << std::endl;

    }
    // else
    // {
    //     std::cerr << "SceneNode "<< name() << " doesn't intersect ray; layer: " << layer << std::endl;
    // }

    return Interpt;
}

InterPoint SceneNode::Sh_intersect(Ray ray, std::string nd, bool drawBx)
{
    InterPoint Interpt;

    // transform ray. Instead of moving the node, move the ray by the inverse transform
    Ray temp_ray = {m_invtrans * ray.pos, m_invtrans * ray.dir};
    // (temp_ray.dir).normalize();

    // std::cerr << "Sh_intersect " << std::endl;

    SceneNode::ChildList::const_iterator it;
    for ( it= m_children.begin(); it != m_children.end(); ++it)
    {
        SceneNode *node = *it;
        InterPoint i = node->intersect(temp_ray, drawBx, 1);
        // std::cout << " shade " << std::endl;

        if (i.hit)
        {
          if (i.obj ->name() != nd)
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
    // else
    // {
    //     std::cerr << "no shadow intersection" << std::endl;
    // }
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
  m_joint_y.init = init;
  m_joint_y.max = max;
}


GeometryNode::GeometryNode(const std::string& name, Primitive* primitive)
  : SceneNode(name),
    m_primitive(primitive)
{
    m_BdBox = m_primitive->findBdBox();
    // std::cerr << "Generate GN "<< name() << " m_BdBox: minP( " << m_BdBox.m_minP << ")" << " maxP( " << m_BdBox.m_maxP << ")" << std::endl;
}

GeometryNode::~GeometryNode()
{
}

BdBox GeometryNode::walk_gl()
{
    if (m_isWalked)
        return m_BdBox;

    BdBox maxBB = get_BdBox();
    maxBB.m_minP= m_trans * maxBB.m_minP;
    maxBB.m_maxP= m_trans * maxBB.m_maxP;

    m_isWalked = true;
    m_BdBox = maxBB;

    // if (name()=="cello")
    // {
    //   std::cerr << name() << " bbox: minP( " << m_BdBox.m_minP << ")" << " maxP( " << m_BdBox.m_maxP << ")" << std::endl;

    // }
    
    // std::cerr << "GeometryNode "<< name() << " bbox: minP( " << m_BdBox.m_minP << ")" << " maxP( " << m_BdBox.m_maxP << ")" << std::endl;
    return m_BdBox;
}

/***********************  findIntersect  **********************************/
InterPoint GeometryNode::intersect(Ray ray, bool drawBx, int layer)
{
  // transform ray. Instead of moving the node, move the ray by the inverse transform
  // std::cout << m_name << " finding intersect" << std::endl;

  Ray temp_ray = {m_invtrans * ray.pos, m_invtrans * ray.dir};
  // (temp_ray.dir).normalize();

  InterPoint InterPt = m_primitive->intersect(temp_ray,drawBx);

  if (InterPt.hit)
  {
    // std::cout << "GeometryNode "<< name() << " is intersected" << std::endl;
    InterPt.obj = this;
    InterPt.uv = get_primitive() -> mapUV(InterPt.pos);
    InterPt.pos = m_trans * InterPt.pos;
    // std::cout << "GeometryNode "<< name() << " modNorm" << std::endl;
    InterPt.n = get_material() -> modifyNormal(InterPt);
    // std::cout << "GeometryNode "<< name() << " modNorm done" << std::endl;
    InterPt.n = m_invtrans.transpose() * InterPt.n;

    // if (name() == "s1")
    //     std::cout <<  name() << "intersect cos" <<  ray.dir.dot (InterPt.n) / (ray.dir.length()*InterPt.n.length()) << std::endl;

    // InterPt.n.normalize();
  }

  else
  {
    // std::cerr << "GeometryNode "<< name() << " is not intersected; layer: " << layer << std::endl;
  }

  return InterPt;
}
