#include "scene.hpp"
#include <iostream>

int Global_count = 0;

SceneNode::SceneNode(const std::string& name)
  : m_name(name)
   ,m_selected(false)
   ,m_parent(NULL)
{
    m_trans.setToIdentity();
    m_id = Global_count;
    Global_count+=10;
}

SceneNode::~SceneNode()
{
}

SceneNode *SceneNode::jointParent() {
// find the first parent thats a joint

  SceneNode *cur = parent();
  while (cur) {
    if (cur->is_joint()) return cur;
    cur = cur->parent();
  }
  return NULL;
}

void SceneNode::toggleSelected() {
  m_selected = !m_selected;
}


void SceneNode::walk_gl(bool picking, QMatrix4x4 transStack, int pick_id) const
{
    QMatrix4x4 temp = transStack * m_trans;
    //traversal
    ChildList::const_iterator it;
    for (it = m_children.begin(); it != m_children.end(); ++it)
    {
        (*it)->walk_gl( picking, temp, pick_id );
    }
}

void SceneNode::rotate(char axis, double angle)
{
//  std::cerr << "Stub: Rotate " << m_name << " around " << axis << " by " << angle << std::endl;
  // Fill me in
  switch (axis)
  {
      case 'x':
          m_trans.rotate(angle, 1, 0, 0);
          break;
      case 'y':
          m_trans.rotate(angle, 0, 1, 0);
          break;
      case 'z':
          m_trans.rotate(angle, 0, 0, 1);
          break;
      default:
          std::cerr << "Stub: Rotate " << m_name << " around " << axis << " by " << angle << std::endl;
  }
}

void SceneNode::scale(const QVector3D& amount)
{
  // Fill me in
  m_trans.scale(amount);
}

void SceneNode::translate(const QVector3D& amount)
{
  // Fill me in
    m_trans.translate(amount);
}

bool SceneNode::is_joint() const
{
  return false;
}

JointNode::JointNode(const std::string& name)
  : SceneNode(name)
{
    m_trans.setToIdentity();
    m_id = Global_count;
    Global_count+=10;
}

JointNode::~JointNode()
{
}
/***********************  JointNode  ***********************/
void JointNode::walk_gl(bool picking, QMatrix4x4 transStack, int pick_id) const
{
//    std::cerr << "JointNode::walk_gl: " << m_name << std::endl;

    QMatrix4x4 temp = transStack * m_trans;
    //traversal

    ChildList::const_iterator it;
    for (it = m_children.begin(); it != m_children.end(); ++it)
    {
        (*it)->walk_gl( picking, temp, pick_id );
    }
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
    m_trans.setToIdentity();
    m_id = Global_count;
    Global_count+=10;
}

GeometryNode::~GeometryNode()
{
}

void GeometryNode::walk_gl(bool picking, QMatrix4x4 transStack, int pick_id) const
{
//    std::cerr << "GeometryNode::walk_gl: " << m_name << std::endl;
    QMatrix4x4 temp = transStack * m_trans;
    double r_f = 0;
    double g_f = 0;
    double b_f = 0;
    if (picking)
    {
        // Convert m_id into an RGB color
        int r = (m_id & 0x000000FF) >>  0;
        int g = (m_id & 0x0000FF00) >>  8;
        int b = (m_id & 0x00FF0000) >> 16;
        r_f = r/255.0f;
        g_f = g/255.0f;
        b_f = b/255.0f;
//        std::cerr<< m_name << ": r " << r_f << " g " << g_f << " b " << b_f << std::endl;
//        std::cerr<< m_name << " m_id = " << m_id << std::endl;
        m_primitive->walk_gl(picking, temp, r_f, g_f, b_f, false);
    }

    else
    {
        if (m_id == pick_id)
        {
//            std::cerr<< m_name << " is picked, m_id=" << m_id << std::endl;
            m_primitive->walk_gl(picking, temp, r_f, g_f, b_f, true);
        }
        else
        {
            m_material->apply_gl(temp);
            m_primitive->walk_gl(picking, temp, r_f, g_f, b_f, false);
        }
    }

}
 
