/***************************************************/
// <author> Haiyu Zhen
// <UserID> h2zhen
// <Student Num> 20552637
// <Email> h2zhen@uwaterloo.ca
// CS 688: Computer Graphics Assignment 2
// <date>  Oct. 2014
/***************************************************/
#include <QtWidgets>
#include <QtOpenGL>
#include <iostream>
#include <cmath>
#include <GL/gl.h>
#include <GL/glu.h>
#include "Viewer.hpp"
// #include "draw.hpp"

#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

using namespace std;

Viewer::Viewer(const QGLFormat& format, QWidget *parent) 
    : QGLWidget(format, parent) 
#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    , mVertexBufferObject(QOpenGLBuffer::VertexBuffer)
    , mVertexArrayObject(this)
#else 
    , mVertexBufferObject(QGLBuffer::VertexBuffer)
#endif
    , m_fov(INIT_FOV)
    , m_near(INIT_NEAR)
    , m_far(INIT_FAR)
    , m_mode(MODEL_ROT)
{
    m_box[0] = QVector4D(-1, 1,-1, 1);
    m_box[1] = QVector4D( 1, 1,-1, 1);
    m_box[2] = QVector4D( 1, 1, 1, 1);
    m_box[3] = QVector4D(-1, 1, 1, 1);
    m_box[4] = QVector4D(-1,-1,-1, 1);
    m_box[5] = QVector4D( 1,-1,-1, 1);
    m_box[6] = QVector4D( 1,-1, 1, 1);
    m_box[7] = QVector4D(-1,-1, 1, 1);

    m_gnomon[0] = QVector4D(0  ,0  ,0  ,  1);
    m_gnomon[1] = QVector4D(0.5,0  ,0  ,  1);
    m_gnomon[2] = QVector4D(0  ,0.5,0  ,  1);
    m_gnomon[3] = QVector4D(0  ,0  ,0.5,  1);

    m_lx = (double)width()*0.05;
    m_ly = (double)height()*0.05;
    m_rx = (double)width()*0.95;
    m_uy = (double)height()*0.95;

    m_lx = 2.0/width() * m_lx - 1.0 ;
    m_ly = 2.0/height() * m_ly - 1.0;
    m_rx = 2.0/width() * m_rx - 1.0 ;
    m_uy = 2.0/height() * m_uy - 1.0;

    set_perspective(m_fov, 1, m_near, m_far);
    m_view = self_trans(0, 0, INIT_Z).inverted() * m_view;
    m_model.translate(0.2, 0.2, 0);


}

QMatrix4x4 Viewer::self_trans(double x, double y, double z){
    QMatrix4x4 transMatrix;
    transMatrix.setRow(0, QVector4D(1, 0, 0, x));
    transMatrix.setRow(1, QVector4D(0, 1, 0, y));
    transMatrix.setRow(2, QVector4D(0, 0, 1, z));
    transMatrix.setRow(3, QVector4D(0, 0, 0, 1));
    return transMatrix;
}
// set perspective
void Viewer::set_perspective(double fov, double aspect,
                             double near, double far)
{
    // convert angle to radian
    double fov_rad = angle2rad(fov);
    double cot = 1.0 / tan(fov_rad / 2);

    double z1   = (far + near ) / ( far - near );
    double z2   = ( -2 * far * near ) / ( far - near );

    QVector4D row_1 ( cot / aspect,  0,    0,  0  );
    QVector4D row_2 ( 0,           cot,    0,  0  );
    QVector4D row_3 ( 0,             0,    -z1, z2 );
    QVector4D row_4 ( 0,             0,    -1,  0  );

    m_projection.setRow(0, row_1);
    m_projection.setRow(1, row_2);
    m_projection.setRow(2, row_3);
    m_projection.setRow(3, row_4);

}

Viewer::~Viewer() {
    // Nothing to do here right now.
}

QSize Viewer::minimumSizeHint() const {
    return QSize(50, 50);
}

QSize Viewer::sizeHint() const {
    return QSize(300, 300);
}

void Viewer::reset_view()
{
    m_fov = INIT_FOV;
    m_near = INIT_NEAR;
    m_far = INIT_FAR;
    m_mode = MODEL_ROT;

    scale_X=1, scale_Y=1, scale_Z=1;

    m_lx = (double)width()*0.05;
    m_ly = (double)height()*0.05;
    m_rx = (double)width()*0.95;
    m_uy = (double)height()*0.95;

    m_lx = 2.0/width() * m_lx - 1.0 ;
    m_ly = 2.0/height() * m_ly - 1.0;
    m_rx = 2.0/width() * m_rx - 1.0 ;
    m_uy = 2.0/height() * m_uy - 1.0;

    m_projection = QMatrix4x4();
    m_scale = QMatrix4x4();
    m_view = QMatrix4x4();
    m_model = QMatrix4x4();

    set_perspective(m_fov, 1, m_near, m_far);
    m_view = self_trans(0, 0, INIT_Z).inverted() * m_view;
    m_model.translate(0.2, 0.2, 0);

    update();
} // reset


void Viewer::initializeGL() {
    // Do some OpenGL setup
    QGLFormat glFormat = QGLWidget::format();
    if (!glFormat.sampleBuffers()) {
        std::cerr << "Could not enable sample buffers." << std::endl;
        return;
    }

    glClearColor(0.7, 0.7, 0.7, 0.0);
    
    if (!mProgram.addShaderFromSourceFile(QGLShader::Vertex, "shader.vert")) {
        std::cerr << "Cannot load vertex shader." << std::endl;
        return;
    }

    if (!mProgram.addShaderFromSourceFile(QGLShader::Fragment, "shader.frag")) {
        std::cerr << "Cannot load fragment shader." << std::endl;
        return;
    }

    if ( !mProgram.link() ) {
        std::cerr << "Cannot link shaders." << std::endl;
        return;
    }

#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    mVertexArrayObject.create();
    mVertexArrayObject.bind();

    mVertexBufferObject.create();
    mVertexBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
#else 

    /*
     * if qt version is less than 5.1, use the following commented code
     * instead of QOpenGLVertexVufferObject. Also use QGLBuffer instead of 
     * QOpenGLBuffer.
     */
    uint vao;
     
    typedef void (APIENTRY *_glGenVertexArrays) (GLsizei, GLuint*);
    typedef void (APIENTRY *_glBindVertexArray) (GLuint);
     
    _glGenVertexArrays glGenVertexArrays;
    _glBindVertexArray glBindVertexArray;
     
    glGenVertexArrays = (_glGenVertexArrays) QGLWidget::context()->getProcAddress("glGenVertexArrays");
    glBindVertexArray = (_glBindVertexArray) QGLWidget::context()->getProcAddress("glBindVertexArray");
     
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);    

    mVertexBufferObject.create();
    mVertexBufferObject.setUsagePattern(QGLBuffer::DynamicDraw);
#endif

    if (!mVertexBufferObject.bind()) {
        std::cerr << "could not bind vertex buffer to the context." << std::endl;
        return;
    }

    mProgram.bind();

    mProgram.enableAttributeArray("vert");
    mProgram.setAttributeBuffer("vert", GL_FLOAT, 0, 3);

    mColorLocation = mProgram.uniformLocation("frag_color");
}


//******************** paintGL *************************//
void Viewer::paintGL() {    
    draw_init();
    set_perspective(m_fov, 1, m_near, m_far);

    // draw viweport rectangle
    set_colour(QColor(1.0, 0.0, 1.0));
    QVector2D ll= QVector2D(m_lx, m_ly); // lower left
    QVector2D lr= QVector2D(m_rx, m_ly);
    QVector2D ul= QVector2D(m_lx, m_uy); // upper left
    QVector2D ur= QVector2D(m_rx, m_uy);

    draw_line(ll, lr);
    draw_line(ll, ul);
    draw_line(ur, ul);
    draw_line(ur, lr);

    // Here is where your drawing code should go.

    //draw model gnomon
    QVector4D gnomon_m[4];
    for (int i = 0; i < 4; i++) {
    gnomon_m[i] = m_view * m_model * m_gnomon[i];
    }
    draw_gnomon(gnomon_m);

    // draw world gnomon
    QVector4D gnomon_w[4];
    for (int i = 0; i < 4; i++) {
    gnomon_w[i] = m_view * m_gnomon[i];
    }
    draw_gnomon(gnomon_w);

    draw_box();
}


//********************** Drawing Functions *********************************//
void Viewer::draw_gnomon(QVector4D* gnomon)
{
    set_colour(QColor(1, 0, 0)); // x axis is red
    draw_line3D(gnomon[0], gnomon[1]);

    set_colour(QColor(0, 1, 0)); // y axis is green
    draw_line3D(gnomon[0], gnomon[2]);

    set_colour(QColor(0, 0, 1)); // z axis is blue
    draw_line3D(gnomon[0], gnomon[3]);
}


void Viewer::draw_box()
{
    QVector4D cube[8];

    // Apply transformations to unit cube
    for( int i = 0; i < 8; i++ )
    {
        cube[i] = m_view * m_model * m_scale * m_box[i];
//        std::cerr<<"cube[i]:" << cube[i].x() << " " <<cube[i].y() << " " <<cube[i].z() << endl;
    }

    set_colour(QColor(0.0, 0.0, 0.0));
    draw_line3D(cube[0], cube[1]);
    draw_line3D(cube[1], cube[2]);
    draw_line3D(cube[2], cube[3]);
    draw_line3D(cube[3], cube[0]);

    set_colour(QColor(0.0, 0.0, 0.0));
    draw_line3D(cube[4], cube[5]);
    draw_line3D(cube[5], cube[6]);
    draw_line3D(cube[6], cube[7]);
    draw_line3D(cube[7], cube[4]);

    set_colour(QColor(0.0, 0.0, 0.0));
    draw_line3D(cube[0], cube[4]);
    draw_line3D(cube[1], cube[5]);
    draw_line3D(cube[2], cube[6]);
    draw_line3D(cube[3], cube[7]);
}

void Viewer::draw_line3D(const QVector4D& p1_, const QVector4D& p2_)
{

    QVector4D A = p1_;
    QVector4D B = p2_;

    // near/far plane clipping
    bool isClip = true;

    QVector4D P_n =  QVector4D(0, 0, m_near,1);
    QVector4D P_f =  QVector4D(0, 0, m_far,1);
    QVector4D n_n =  QVector4D(0, 0, NEAR_NORM,0);
    QVector4D n_f =  QVector4D(0, 0, FAR_NORM,0);

    isClip &= lineClip(A, B, P_n, n_n);//near plane clipping
    isClip &= lineClip(A, B, P_f, n_f);//far plane clipping

    if (!isClip)
    {
//        std::cerr << "m_near:" << m_near << " m_far:" << m_far << endl;
//        std::cerr << "Line (" << A.x() << ","<< A.y() << ","<< A.z() << ") - "
//                       << "(" << B.x() << ","<< B.y() << ","<< B.z() << ") "
//                  << "clip N/F discarded" << endl;
        return;
    }

    // projective transformations
    QVector4D p1 = m_projection * A;
    QVector4D p2 = m_projection * B;

    // homogenization
    p1.setX(p1.x() * 1.0/p1.w());
    p1.setY(p1.y() * 1.0/p1.w());

    p2.setX(p2.x() * 1.0/p2.w());
    p2.setY(p2.y() * 1.0/p2.w());

    // viewport mapping
    QVector2D A_vp = viewport_map(QVector2D(p1.x(), p1.y()));
    QVector2D B_vp = viewport_map(QVector2D(p2.x(), p2.y()));

//    draw_line(A_vp,B_vp);

    // viewport clipping
    isClip &= lineClip2D(A_vp, B_vp, QVector2D(m_lx, m_uy), QVector2D( 0, -1));//top clipping
    isClip &= lineClip2D(A_vp, B_vp, QVector2D(m_lx, m_ly), QVector2D( 0,  1));//bottom clipping
    isClip &= lineClip2D(A_vp, B_vp, QVector2D(m_lx, m_uy), QVector2D( 1,  0));//left clipping
    isClip &= lineClip2D(A_vp, B_vp, QVector2D(m_rx, m_ly), QVector2D(-1,  0));//right clipping22

    if (!isClip)
    {
        return;
    }

    draw_line(A_vp,B_vp);
}

// viewport mapping
QVector2D Viewer::viewport_map(const QVector2D &p)
{
    double pv_x = (p.x() + 1) / 2 *(m_rx - m_lx) + m_lx;
    double pv_y = (p.y() + 1) / 2 *(m_uy - m_ly) + m_ly;

    return QVector2D (pv_x, pv_y);
}

// Clipping Line in 3D
bool Viewer::lineClip(QVector4D& A, QVector4D& B, const QVector4D& P, const QVector4D& normal)
{
    double wecA  = QVector4D::dotProduct((A-P), normal);
    double wecB  = QVector4D::dotProduct((B-P), normal);

    if (wecA < 0 && wecB < 0) {
        return false;
    }
    if (wecA >= 0 && wecB >= 0)
    {
        return true;
    }
    else
    {
        double t = wecA / (wecA - wecB);
        if (wecA < 0) {
            A = A + t * (B - A);
        }
        else {
            B = A + t * (B-A);
        }
    }

    return true;
}

// Clipping Line in 2D
bool Viewer::lineClip2D(QVector2D& A, QVector2D& B, const QVector2D& P, const QVector2D& normal)
{
    // dot product
    double wecA  = (A - P).x() * normal.x() + (A - P).y() * normal.y() ;
    double wecB  = (B - P).x() * normal.x() + (B - P).y() * normal.y() ;

    if (wecA < 0 && wecB < 0) {
        return false;
    }
    if (wecA >= 0 && wecB >= 0)
    {
        return true;
    }
    else
    {
        double t = wecA / (wecA - wecB);
        if (wecA < 0) {
            A = A + t * (B - A);
        }
        else {
            B = A + t * (B-A);
        }
    }

    return true;
}
// ******************* Do Not Touch ************************ //
void Viewer::draw_line(const QVector2D& p1, const QVector2D& p2) {

  const GLfloat lineVertices[] = {
    p1.x(), p1.y(), 1.0,
    p2.x(), p2.y(), 1.0
  };

  mVertexBufferObject.allocate(lineVertices, 3 * 2 * sizeof(float));

  glDrawArrays(GL_LINES, 0, 2);
}

void Viewer::set_colour(const QColor& col)
{
  mProgram.setUniformValue(mColorLocation, col.red(), col.green(), col.blue());
}

void Viewer::draw_init() {
    glClearColor(0.7, 0.7, 0.7, 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (double)width(), 0.0, (double)height());
    glViewport(0, 0, width(), height());

    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glLineWidth(1.0);
}


/*********************        Mouse Events          ********************************/
void Viewer::mousePressEvent ( QMouseEvent * event ) {
    lastMousePosition = event->pos();

    if (m_mode == VIEWPORT)
    {
        m_x1 = lastMousePosition.x();
        m_y1 = lastMousePosition.y();
    }
}

void Viewer::mouseReleaseEvent ( QMouseEvent * event ) {
//    std::cerr << "Stub: button " << event->button() << " released\n";
}

void Viewer::mouseMoveEvent ( QMouseEvent * event )
{
    double dx = event->x() - lastMousePosition.x();
//    std::cerr << "dx = " << dx << std::endl;
    lastMousePosition = event->pos();

    QMatrix4x4 translationMat,translationMat_V;
    QMatrix4x4 rotMat,rotMat_V;
    QMatrix4x4 scaleMat;

    switch(m_mode) {
        case VIEW_ROT:
        {
            double rotVal = dx * 20;
            double theta = angle2rad(rotVal);
            if (event->buttons() & Qt::LeftButton) //x axis
            {
                rotMat_V.rotate(theta, 1, 0, 0);
            }

            if (event->buttons() & Qt::RightButton) // y axis
            {
                rotMat_V.rotate(theta, 0, 1, 0);
            }

            if (event->buttons() & Qt::MidButton) // z axis
            {
                rotMat_V.rotate(theta, 0, 0, 1);
            }
            break;
        }
        case VIEW_TRANS:
        {
            double transVal = dx/100.0;
            if (event->buttons() & Qt::LeftButton) //x axis
            {
                 translationMat_V.translate(transVal,0,0);
            }

            if (event->buttons() & Qt::RightButton) // y axis
            {
                  translationMat_V.translate(0,transVal,0);
            }

            if (event->buttons() & Qt::MidButton) // z axis
            {
                  translationMat_V.translate(0,0,transVal);
            }
            break;
        }
        case VIEW_PERS:
        {
            if (event->buttons() & Qt::LeftButton) //x axis
            {
                m_fov += dx;
                if (m_fov < 5) m_fov = 5;
                else if (m_fov > 160) m_fov = 160;
            }

            if (event->buttons() & Qt::RightButton) // y axis
            {
                if (std::abs(m_near+dx) < std::abs(m_far))
                    m_near += dx * 0.05;
            }

            if (event->buttons() & Qt::MidButton) // z axis
            {
                if (std::abs(m_near) < std::abs(m_far + dx))
                    m_far += dx * 0.05;
            }
            break;
        }
        case MODEL_ROT:
        {
            double rotVal = dx * 20;
            double theta = angle2rad(rotVal);
            if (event->buttons() & Qt::LeftButton) //x axis
            {
                rotMat.rotate(theta, 1, 0, 0);
            }

            if (event->buttons() & Qt::RightButton) // y axis
            {
                rotMat.rotate(theta, 0, 1, 0);
            }

            if (event->buttons() & Qt::MidButton) // z axis
            {
                rotMat.rotate(theta, 0, 0, 1);
            }
            break;
        }
        case MODEL_TRANS:
        {
            double transVal = dx/100.0;
            if (event->buttons() & Qt::LeftButton) //x axis
            {
                 translationMat.translate(transVal,0,0);
            }

            if (event->buttons() & Qt::RightButton) // y axis
            {
                  translationMat.translate(0,transVal,0);
            }

            if (event->buttons() & Qt::MidButton) // z axis
            {
                  translationMat.translate(0,0,transVal);
            }
            break;
        }
        case MODEL_SCALE:
        {
            double scaleVal = dx * 0.05;

            // avoid negative scaling
            if (scaleVal < -1)
                scaleVal = -1 + 1.0 * std::pow(10,-1);

            if (event->buttons() & Qt::LeftButton) //x axis
            {
                if (scale_X * (scaleVal + 1) > std::pow(10,-3))
                {
                    scale_X *= (scaleVal + 1);
                    scaleMat.setRow(0, QVector4D(scaleVal + 1, 0, 0, 0));
                }
//                std::cerr << "scale_X: " << scale_X << endl;
            }

            if (event->buttons() & Qt::RightButton) // y axis
            {
                if (scale_Y * (scaleVal + 1) > std::pow(10,-3))
                {
                    scale_Y *= scaleVal + 1;
                    scaleMat.setRow(1, QVector4D(0, scaleVal + 1, 0, 0));
                }
//                std::cerr << "scale_Y: " << scale_Y << endl;
            }

            if (event->buttons() & Qt::MidButton) // z axis
            {
                if (scale_Z * (scaleVal + 1) > std::pow(10,-3))
                {
                    scale_Z *= scaleVal + 1;
                    scaleMat.setRow(2, QVector4D(0, 0, scaleVal + 1, 0));
                }
//                std::cerr << "scale_Z: " << scale_Z << endl;

            }
            break;
        }
        case VIEWPORT:
        {
//            std::cerr << "m_x2, m_y2 " << event->pos().x() << ", " << event->pos().y() <<"\n";
            m_x2 = lastMousePosition.x();
            m_y2 = lastMousePosition.y();

            double l_x, l_y, r_x, u_y;
            l_x = std::min( m_x1, m_x2 );
            l_y = std::min( m_y1, m_y2 );
            r_x = std::max( m_x1, m_x2 );
            u_y = std::max( m_y1, m_y2 );

            if (l_x < 0)         l_x = 0;
            if (l_y < 0)         l_y = 0;
            if (r_x > width())   r_x = width();
            if (u_y > height())  u_y = height();

            m_lx = 2.0/width() * l_x - 1.0 ;
            m_ly = 2.0/height() * l_y - 1.0;
            m_rx = 2.0/width() * r_x - 1.0 ;
            m_uy = 2.0/height() * u_y - 1.0;

            m_ly = -m_ly;
            m_uy = -m_uy;

            double temp_y;
            temp_y = m_ly;
            m_ly = m_uy;
            m_uy = temp_y;

            break;
        }
    }// end case

    //apply to global transformation matrix
    m_model *= rotMat * translationMat;
    m_view  = (rotMat_V * translationMat_V).inverted() * m_view;
    m_scale *= scaleMat;

    update();
}


double Viewer::angle2rad(double angle)
{
    return angle * (2 * M_PI / 360.0);
}

const char* Viewer::label_text()
{
    std::stringstream ss;

    switch(m_mode)
    {
        case Viewer::VIEW_ROT:
          ss << "View Rotate";
          break;
        case Viewer::VIEW_TRANS:
          ss << "View Translate";
          break;
        case Viewer::VIEW_PERS:
          ss << "View Perspective";
          break;
        case Viewer::MODEL_ROT:
          ss << "Model Rotate";
          break;
        case Viewer::MODEL_TRANS:
          ss << "Model Translate";
          break;
        case Viewer::MODEL_SCALE:
          ss << "Model Scale";
          break;
        case Viewer::VIEWPORT:
          ss << "Viewport";
          break;
    }
    ss << "\nFOV: " << m_fov
                    << "  Near: " << m_near << "  Far: " << m_far;

    const std::string tmp = ss.str();
    const char* cstr = tmp.c_str();
    return cstr;
}
