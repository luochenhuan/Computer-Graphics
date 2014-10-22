/***************************************************/
// <author> Haiyu Zhen
// <UserID> h2zhen
// <Student Num> 20552637
// <Email> h2zhen@uwaterloo.ca
// CS 688: Computer Graphics Assignment 2
// <date>  Oct. 2014
/***************************************************/
#ifndef CS488_VIEWER_HPP
/***************************************************/
// <author> Haiyu Zhen
// <UserID> h2zhen
// <Student Num> 20552637
// <Email> h2zhen@uwaterloo.ca
// CS 688: Computer Graphics Assignment 2
// <date>  Oct. 2014
/***************************************************/
#define CS488_VIEWER_HPP

#include <QGLWidget>
#include <QGLShaderProgram>
#include <QMatrix4x4>

#include <QtGlobal>
#include <sstream>

#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#else 
#include <QGLBuffer>
#endif

#ifndef INIT_FOV
#define INIT_FOV   60
#endif

#ifndef INIT_NEAR
#define INIT_NEAR -2
#endif

#ifndef INIT_FAR
#define INIT_FAR  -10
#endif

#ifndef NEAR_NORM
#define NEAR_NORM -1
#endif

#ifndef FAR_NORM
#define FAR_NORM 1
#endif

#ifndef M_PI
#define M_PI 3.14159
#endif

#ifndef INIT_Z
#define INIT_Z   4
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

    // *** Fill in these functions (in viewer.cpp) ***

    // Set the parameters of the current perspective projection using
    // the semantics of gluPerspective().
    void set_perspective(double fov, double aspect,
                         double near, double far);

    // Restore all the transforms and perspective parameters to their
    // original state. Set the viewport to its initial size.
    void reset_view();

    // ********************* Fill me in **************************** //
    enum Mode {
      VIEW_ROT, VIEW_TRANS, VIEW_PERS, MODEL_ROT, MODEL_TRANS, MODEL_SCALE, VIEWPORT
    };
    void set_mode(Mode mode) {m_mode = mode;}

    void draw_box();
    void draw_gnomon(QVector4D* gnomon);

    const char* label_text();
    // perspective
    double m_fov;
    double m_near;
    double m_far;

    Mode m_mode;

protected:

    // Events we implement

    // Called when GL is first initialized
    virtual void initializeGL();
    // Called when our window needs to be redrawn
    virtual void paintGL();
    // Called when a mouse button is pressed
    virtual void mousePressEvent ( QMouseEvent * event );
    // Called when a mouse button is released
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    // Called when the mouse moves
    virtual void mouseMoveEvent ( QMouseEvent * event );
 
    // Draw a line -- call draw_init first!
    void draw_line(const QVector2D& p1, const QVector2D& p2) ;
    void draw_line3D(const QVector4D& p1, const QVector4D& p2) ;

    // Set the current colour
    void set_colour(const QColor& col);

    // Call this before you begin drawing. Width and height are the width
    // and height of the GL window.
    void draw_init();
private:

#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    QOpenGLBuffer mVertexBufferObject;
    QOpenGLVertexArrayObject mVertexArrayObject;
#else 
    QGLBuffer mVertexBufferObject;
#endif

    QGLShaderProgram mProgram;

    int mColorLocation;
    QPoint lastMousePosition;

    // *** Fill me in ***
    // You will want to declare some more matrices here
    QMatrix4x4 m_projection;
    QMatrix4x4 m_model;
    QMatrix4x4 m_view;
    QMatrix4x4 m_scale;


    // original cube coordinates
    QVector4D m_box[8];
    QVector4D m_gnomon[4];


    double m_x1, m_x2, m_y1, m_y2;
    double m_lx, m_rx, m_ly, m_uy;
    double scale_X=1, scale_Y=1, scale_Z=1;

    QVector2D viewport_map(const QVector2D& p);
    bool lineClip(QVector4D& A, QVector4D& B, const QVector4D& P, const QVector4D& normal);
    bool lineClip2D(QVector2D& A, QVector2D& B, const QVector2D& P, const QVector2D& normal);

    double angle2rad(double angle);

    QMatrix4x4 self_trans(double x, double y, double z);

};

#endif
