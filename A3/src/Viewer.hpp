#ifndef CS488_VIEWER_HPP
#define CS488_VIEWER_HPP

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QMatrix4x4>
#include <QtGlobal>
#include "scene_lua.hpp"

#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#else 
#include <QGLBuffer>
#endif


#ifndef LONGNUM
#define LONGNUM 200
#endif

#ifndef LATNUM
#define LATNUM 200
#endif
class Viewer : public QGLWidget {
    
    Q_OBJECT

public:
    Viewer(const QGLFormat& format, QWidget *parent = 0);
    virtual ~Viewer();
    
    QSize minimumSizeHint() const;
    QSize sizeHint() const;

    // If you want to render a new frame, call do not call paintGL(),
    // instead, call update() to ensure that the view gets a paint 
    // event.
    SceneNode* m_root;

    enum Mode {
    POS_ORI,
    JOINTS
    };

    void initializeSphere();
    void initializeCircle();
    std::vector<GLfloat> sphereVec;
    std::vector<GLfloat> circleVec;
    std::vector<int> pickIdVec;
    std::vector<SceneNode> pickJointVec;

    void setMode(Mode mode){ m_mode = mode;}
    void setMaterial(const QColor& kd, const QColor& ks, float shininess,QMatrix4x4 m);
    void set_colour(const QColor& col);
    void set_colour(float r, float g, float b);
    void setDrawCircle() {m_drawCircle = !m_drawCircle;update();}
    void set_zbuffer() {m_zBuffer = !m_zBuffer;update();}
    void set_backcull() {m_backCull = !m_backCull;update();}
    void set_frontcull() {m_frontCull = !m_frontCull;update();}

    void reset_pos();

    void reset_ori();

    void draw_trackball_circle();
    void draw_sphere(QMatrix4x4 m_trans);

    void reset();

    QMatrix4x4 modelMatrix;
    QMatrix4x4 m_trackballRotation;

    bool m_frontCull;
    bool m_backCull;
    bool m_zBuffer;
    bool m_drawCircle;
    bool m_picking;
    int pickedID;

protected:

    // Events we implement

    // Called when GL is first initialized
    virtual void initializeGL();
    // Called when our window needs to be redrawn
    virtual void paintGL();
    // Called when the window is resized (formerly on_configure_event)
    virtual void resizeGL(int width, int height);
    // Called when a mouse button is pressed
    virtual void mousePressEvent ( QMouseEvent * event );
    // Called when a mouse button is released
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    // Called when the mouse moves
    virtual void mouseMoveEvent ( QMouseEvent * event );
    
    // Draw a circle for the trackball, with OpenGL commands.
    // Assumes the context for the viewer is active.

private:

    QMatrix4x4 getCameraMatrix(bool getPers=true);
    void translateWorld(float x, float y, float z);
    void rotateWorld(float x, float y, float z);
    void scaleWorld(float x, float y, float z);

    QMatrix4x4 vAxisRotMatrix(float fVecX, float fVecY, float fVecZ);
    void vCalcRotVec(float fNewX, float fNewY,
                             float fOldX, float fOldY,
                             float fDiameter,
                             float *fVecX, float *fVecY, float *fVecZ);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    QOpenGLBuffer mCircleBufferObject;
    QOpenGLVertexArrayObject mVertexArrayObject;
#else 
    QGLBuffer mBufferObject;
//    QGLBuffer mSphereBufferObject;
//    QGLBuffer mColorBufferObject;
#endif
    
    int mMvpMatrixLocation;
    int mMvMatrixLocation;
    int mColorLocation;

    QPoint lastMousePosition;

    QMatrix4x4 mPerspMatrix;
    QMatrix4x4 mTransformMatrix;

    QGLShaderProgram mProgram;

    Mode m_mode;

    GLfloat databuffer[120 + 6*LATNUM*LONGNUM];

    // lighting parameters
    int mLa,mLd,mLs;
    int mKa,mKd,mKs;
    int mShininess;
    int mNormMatPosition;
    int mLightPos;
    int mIsShading;

};

#endif
