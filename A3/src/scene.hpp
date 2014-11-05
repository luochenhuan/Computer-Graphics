#ifndef SCENE_HPP
#define SCENE_HPP

#include <list>
#include "algebra.hpp"
#include "primitive.hpp"
#include "material.hpp"



class SceneNode {
public:
  SceneNode(const std::string& name);
  virtual ~SceneNode();

  virtual void walk_gl(bool picking = false, QMatrix4x4 transStack = QMatrix4x4(), int pick_id = 6710886) const;

  const QMatrix4x4& get_transform() const { return m_trans; }
  const QMatrix4x4& get_inverse() const { return m_invtrans; }
  
  void set_transform(const QMatrix4x4& m)
  {
    m_trans = m;
    m_invtrans = m.inverted();
  }

  void set_transform(const QMatrix4x4& m, const QMatrix4x4& i)
  {
    m_trans = m;
    m_invtrans = i;
  }

  void add_child(SceneNode* child)
  {
    m_children.push_back(child);
  }

  void remove_child(SceneNode* child)
  {
    m_children.remove(child);
  }

  // Callbacks to be implemented.
  // These will be called from Lua.
  void rotate(char axis, double angle);
  void scale(const QVector3D& amount);
  void translate(const QVector3D& amount);

  // Returns true if and only if this node is a JointNode
  virtual bool is_joint() const;

  bool is_selected() { return m_selected; }
  void toggleSelected();
  bool m_selected;

  SceneNode *parent() { return m_parent; }
  SceneNode *jointParent();

protected:
  
  // Useful for picking
  int m_id;
  std::string m_name;
  SceneNode *m_parent;

  // Transformations
  QMatrix4x4 m_trans;
  QMatrix4x4 m_invtrans;

  // Hierarchy
  typedef std::list<SceneNode*> ChildList;
  ChildList m_children;
};

/************************** JointNode ****************************/
class JointNode : public SceneNode {
public:
  JointNode(const std::string& name);
  virtual ~JointNode();

  virtual void walk_gl(bool picking = false, QMatrix4x4 transStack = QMatrix4x4(), int pick_id = 6710886) const;

  virtual bool is_joint() const;

  void set_joint_x(double min, double init, double max);
  void set_joint_y(double min, double init, double max);

  struct JointRange {
    double min, init, max;
  };

protected:
  JointRange m_joint_x, m_joint_y;
};

/************************** GeometryNode ****************************/
class GeometryNode : public SceneNode {
public:
  GeometryNode(const std::string& name,
               Primitive* primitive);
  virtual ~GeometryNode();

  virtual void walk_gl(bool picking = false, QMatrix4x4 transStack = QMatrix4x4(), int pick_id = 6710886) const;

  const Material* get_material() const;
  Material* get_material();

  void set_material(Material* material)
  {
    m_material = material;
  }

protected:
  Material* m_material;
  Primitive* m_primitive;
};

#endif
