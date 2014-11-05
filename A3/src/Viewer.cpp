#include <QtWidgets>
#include <QtOpenGL>
#include "Viewer.hpp"
#include <iostream>
#include <math.h>
#include <GL/glu.h>


#ifndef GL_MULTISAMPLE
#define GL_MULTISAMPLE 0x809D
#endif

Viewer::Viewer(const QGLFormat& format, QWidget *parent) 
    : QGLWidget(format, parent) 
#if (QT_VERSION >= QT_VERSION_CHECK(5, 1, 0))
    , mBufferObject(QOpenGLBuffer::VertexBuffer)
    , mVertexArrayObject(this)
#else 
    , mBufferObject(QGLBuffer::VertexBuffer)
#endif
    , m_mode(POS_ORI)
    , m_drawCircle(false)
    , m_frontCull(false)
    , m_backCull(false)
    , m_zBuffer(false)
    , m_picking(false)
{
    initializeSphere();
    initializeCircle();
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

void Viewer::initializeGL() {
    QGLFormat glFormat = QGLWidget::format();
    if (!glFormat.sampleBuffers()) {
        std::cerr << "Could not enable sample buffers." << std::endl;
        return;
    }

    glShadeModel(GL_SMOOTH);
    glClearColor( 0.4, 0.4, 0.4, 0.0 );
    glEnable(GL_DEPTH_TEST);
    
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

    mBufferObject.create();
    mBufferObject.setUsagePattern(QOpenGLBuffer::StaticDraw);
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

#endif

    for(size_t i=0; i<120; ++i) {
        databuffer[i] = circleVec[i];
    }

    for(size_t i=0; i< 3*LATNUM*(LONGNUM+1)*2; ++i) {
        databuffer[i+120] = sphereVec[i];
    }

    mBufferObject.create();
    mBufferObject.setUsagePattern(QGLBuffer::StaticDraw);

    if (!mBufferObject.bind()) {
        std::cerr << "could not bind vertex 1.buffer to the context." << std::endl;
        return;
    }
    mBufferObject.allocate(databuffer, (40 * 3 + 3*LATNUM*(LONGNUM+1)*2) * sizeof(float));
//    mBufferObject.allocate(&circleVec[0], 40 * 3 * sizeof(float));

//    mBufferObject.allocate(&sphereVec[0], 3*LATNUM*(LONGNUM+1)*2 * sizeof(float));

    mProgram.bind();
    mProgram.enableAttributeArray("vertPos");
    mProgram.setAttributeBuffer("vertPos", GL_FLOAT, 0, 3);

    mMvpMatrixLocation = mProgram.uniformLocation("mvpMatrix");
    mMvMatrixLocation = mProgram.uniformLocation("mvMatrix");
    mColorLocation = mProgram.uniformLocation("frag_color");

    mLa = mProgram.uniformLocation("La");
    mLd = mProgram.uniformLocation("Ld");
    mLs = mProgram.uniformLocation("Ls");

    mKa = mProgram.uniformLocation("Ka");
    mKd = mProgram.uniformLocation("Kd");
    mKs = mProgram.uniformLocation("Ks");
    mShininess = mProgram.uniformLocation("Shininess");

    mNormMatPosition = mProgram.uniformLocation("normMat");
    mLightPos = mProgram.uniformLocation("LightPos");

    mIsShading = mProgram.uniformLocation("isShading");


}

void Viewer::paintGL() {
    // Clear framebuffer
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    /************ Set up lighting ***************/
    // set up light source
    mProgram.setUniformValue(mLa, 0.5, 0.5, 0.5);
    mProgram.setUniformValue(mLd, 0.5, 0.5, 0.5);
    mProgram.setUniformValue(mLs, 0, 0, 0);// turn off spec by default
    mProgram.setUniformValue(mLightPos, 0, 5.0, 10.0, 1.0);

    if (m_frontCull || m_backCull) {
        glEnable(GL_CULL_FACE);
        if (m_backCull && m_frontCull) {
          glCullFace(GL_FRONT_AND_BACK);
        }
        else if (m_frontCull) {
          glCullFace(GL_FRONT);
        }
        else {
          glCullFace(GL_BACK);
        }
      }
      else {
        glDisable(GL_CULL_FACE);
      }
      if (m_zBuffer) {
        glEnable(GL_DEPTH_TEST);
        glDepthMask(true);
      }
      else {
        glDisable(GL_DEPTH_TEST);
        glDepthMask(false);
      }

    if (m_drawCircle == true)
      draw_trackball_circle();

    // Draw stuff
    m_root->walk_gl(m_picking,QMatrix4x4(),pickedID);


}

void Viewer::resizeGL(int width, int height) {
    if (height == 0) {
        height = 1;
    }

    mPerspMatrix.setToIdentity();
    mPerspMatrix.perspective(60.0, (float) width / (float) height, 0.001, 1000);

    glViewport(0, 0, width, height);
}

void Viewer::reset()
{
    modelMatrix = QMatrix4x4();
    m_trackballRotation = QMatrix4x4();

    m_frontCull = false;
    m_backCull = false;
    m_zBuffer = false;
    m_drawCircle = false;
    m_mode = POS_ORI;
    m_picking = false;

    initializeSphere();
    initializeCircle();

    update();
}

/************************** draw_sphere ****************************/
void Viewer::draw_sphere(QMatrix4x4 m_trans)
{
    // Bind buffer object
    mBufferObject.bind();
    mProgram.setUniformValue(mMvpMatrixLocation, getCameraMatrix() * modelMatrix * m_trackballRotation * m_trans);

    // Draw buffer
    glDrawArrays(GL_TRIANGLE_STRIP, 120, LATNUM * (LONGNUM+1) * 2);
    mBufferObject.release();
}


/************************** draw_trackball_circle ****************************/
void Viewer::draw_trackball_circle()
{
    int current_width = width();
    int current_height = height();

    set_colour(QColor(0.0, 0.0, 0.0));

    // Set orthographic Matrix
    QMatrix4x4 orthoMatrix;
    orthoMatrix.ortho(0.0, (float)current_width,
           0.0, (float)current_height, -0.1, 0.1);

    // Translate the view to the middle
    QMatrix4x4 transformMatrix;
    transformMatrix.translate(width()/2.0, height()/2.0, 0.0);
    transformMatrix.scale(12,12,1);

    // Bind buffer object
    mBufferObject.bind();

    mProgram.setUniformValue(mMvpMatrixLocation, orthoMatrix * transformMatrix);

    // Draw buffer
    glDrawArrays(GL_LINE_LOOP, 0, 40);
    mBufferObject.release();
}



/************************  Drawing Functions  **************************/
QMatrix4x4 Viewer::getCameraMatrix(bool getPers) {
    // Todo: Ask if we want to keep this.
    QMatrix4x4 vMatrix;

    QMatrix4x4 cameraTransformation;
    QVector3D cameraPosition = cameraTransformation * QVector3D(0, 0, 20.0);
    QVector3D cameraUpDirection = cameraTransformation * QVector3D(0, 1, 0);

    vMatrix.lookAt(cameraPosition, QVector3D(0, 0, 0), cameraUpDirection);
    if (getPers == true)
        return mPerspMatrix * vMatrix * mTransformMatrix;
    else
        return  mTransformMatrix;
}


/************************  Set Lighting  **************************/
void Viewer::set_colour(const QColor& col)
{
//    std::cerr<< "set color" << ": r " << col.red()  << std::endl;
    mProgram.setUniformValue(mIsShading, 0);
    mProgram.setUniformValue(mColorLocation, col.red(), col.green(), col.blue());

}

void Viewer::set_colour(float r, float g, float b)
{
//    std::cerr<< "float set color : r " << r << std::endl;
    mProgram.setUniformValue(mIsShading, 0);
    mProgram.setUniformValue(mColorLocation, r, g, b);

}

void Viewer::setMaterial(const QColor& kd, const QColor& ks, float shininess, QMatrix4x4 m)
{
    // set up material
    mProgram.setUniformValue(mIsShading, 1);
    QColor ka = QColor(20,20,20);
    mProgram.setUniformValue(mKa, ka.red()/255.0, ka.green()/255.0, ka.blue()/255.0);
    mProgram.setUniformValue(mKd, kd.red()/255.0, kd.green()/255.0, kd.blue()/255.0);
    mProgram.setUniformValue(mKs, ks.red()/255.0, ks.green()/255.0, ks.blue()/255.0);
    mProgram.setUniformValue(mShininess, shininess);
    mProgram.setUniformValue(mMvMatrixLocation, getCameraMatrix(false) * m_trackballRotation * modelMatrix *m);
//    std::cerr<< "setMaterial Ks: r " << ks.red()/255.0 << std::endl;

    // set up norm
    mProgram.setUniformValue(mNormMatPosition, (getCameraMatrix(false) * m_trackballRotation * modelMatrix *  m).normalMatrix());
}


/************************  Mouse Events  **************************/
void Viewer::mousePressEvent ( QMouseEvent * event ) {
//    std::cerr << "Stub: button " << event->button() << " pressed\n";
    lastMousePosition = event->pos();

    if (m_mode == JOINTS)
    {
        // Read the pixel at the center of the screen.
        // You can also use glfwGetMousePos().
        // Ultra-mega-over slow too, even for 1 pixel,
        // because the framebuffer is on the GPU.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        m_picking = true;
        m_root->walk_gl(m_picking);

        unsigned char data[4];
        glReadPixels(event->x(), height() - event->y(),1,1, GL_RGBA, GL_UNSIGNED_BYTE, data);
    //    std::cerr << "data[0] " << (unsigned int)data[0] << " \n";

        pickedID =
                 data[0] +
                 data[1] * 256 +
                 data[2] * 256*256;

//        std::cerr << "pickedID " << pickedID << " \n";
        pickIdVec.push_back(pickedID);

        m_picking = false;
        update();
    }

}

void Viewer::mouseReleaseEvent ( QMouseEvent * event ) {
//    std::cerr << "Stub: button " << event->button() << " released\n";
//    lastMousePosition = event->pos();
}

void Viewer::mouseMoveEvent ( QMouseEvent * event ) {
//    std::cerr << "Stub: Motion at " << event->x() << ", " << event->y() << std::endl;
    double dx = event->x() - lastMousePosition.x();
    double dy = event->y() - lastMousePosition.y();

//    std::cerr << "dx " << dx << "dy " << dy << std::endl;

    switch(m_mode)
    {
    case POS_ORI:
    {
        if (event->buttons() & Qt::LeftButton) //B1
        {
            double transVal_x = dx/50;
            double transVal_y = -1.0 * dy/50;
//            std::cerr << "POS_ORI: " << transVal_x << " " << transVal_y << "released\n";

            modelMatrix.translate(transVal_x, transVal_y, 0);
        }

        if (event->buttons() & Qt::MidButton) //B2
        {
            double transVal_z = 1.0 * dy/50;

            modelMatrix.translate(0, 0, transVal_z);
        }

        if (event->buttons() & Qt::RightButton) //B3
        {
            //Track ball rotations are being used.
            float fDiameter;
            int iCenterX, iCenterY;
            float fNewModX, fNewModY, fOldModX, fOldModY;

            /* vCalcRotVec expects new and old positions in relation to the center of the
            * trackball circle which is centered in the middle of the window and
            * half the smaller of nWinWidth or nWinHeight.
            */
            fDiameter = (width() < height()) ? (float)width() * 0.5f : (float)height() * 0.5f;
            iCenterX = width() / 2;
            iCenterY = height() / 2;

            fOldModX = lastMousePosition.x() - iCenterX;
            fOldModY = lastMousePosition.y() - iCenterY;
            fNewModX = event->x() - iCenterX;
            fNewModY = event->y() - iCenterY;

            float  fRotVecX, fRotVecY, fRotVecZ;

            vCalcRotVec(fNewModX, fNewModY,
                         fOldModX, fOldModY,
                         fDiameter,
                         &fRotVecX, &fRotVecY, &fRotVecZ);
            /* Negate Y component since Y axis increases downwards
            * in screen space and upwards in OpenGL.
            */
            QMatrix4x4 mNewMat = vAxisRotMatrix(fRotVecX, -fRotVecY, fRotVecZ);

            // Since all these matrices are meant to be loaded
            // into the OpenGL matrix stack, we need to transpose the
            // rotation matrix (since OpenGL wants rows stored
            // in columns)

            //vTransposeMatrix(mNewMat);
            //vRightMultiply(mRotations, mNewMat);

            m_trackballRotation = m_trackballRotation * mNewMat ;
        }
    }
    case JOINTS:
    {

    }
    }// end switch

    lastMousePosition = event->pos();
    update();
}

/************************  initializeSphere  **************************/
void Viewer::initializeSphere(){
    for(int i = 0; i <= LONGNUM; i++)
    {
        double lat_top = 2* M_PI * (-0.5 + (double) (i - 1) / LONGNUM);
        double sin_top  = sin(lat_top);
        double cos_top =  cos(lat_top);

        double lat_bottom = 2 * M_PI * (-0.5 + (double) i / LONGNUM);
        double sin_bottom = sin(lat_bottom);
        double cos_bottom = cos(lat_bottom);

        for(int j = 0; j < LATNUM; j++)
        {
                double lon = 2 * M_PI * (double) (j - 1) / LATNUM;
                double cos_width = cos(lon);
                double sin_width = sin(lon);

                sphereVec.push_back(cos_width * cos_top);
                sphereVec.push_back(sin_width * cos_top);
                sphereVec.push_back(sin_top);

                sphereVec.push_back(cos_width * cos_bottom);
                sphereVec.push_back(sin_width * cos_bottom);
                sphereVec.push_back(sin_bottom);
        }
    }
}

/************************  initializeCircle  **************************/
void Viewer::initializeCircle(){
    //initialize the circle
    double radius = width() < height() ?
        (float)width() * 0.25 : (float)height() * 0.25;

    for(size_t i=0; i<40; ++i) {
        circleVec.push_back (radius * cos(i*2*M_PI/40));
        circleVec.push_back (radius * sin(i*2*M_PI/40));
        circleVec.push_back (0.0);
    }
}


/************************  trackball  **************************/
void Viewer::vCalcRotVec(float fNewX, float fNewY,
                 float fOldX, float fOldY,
                 float fDiameter,
                 float *fVecX, float *fVecY, float *fVecZ) {


   float fNewVecX, fNewVecY, fNewVecZ,        /* Vector corresponding to new mouse location */
         fOldVecX, fOldVecY, fOldVecZ,        /* Vector corresponding to old mouse location */
         fLength;

   /* Vector pointing from center of virtual trackball to
    * new mouse position
    */
   fNewVecX    = fNewX * 2.0 / fDiameter;
   fNewVecY    = fNewY * 2.0 / fDiameter;
   fNewVecZ    = (1.0 - fNewVecX * fNewVecX - fNewVecY * fNewVecY);

   /* If the Z component is less than 0, the mouse point
    * falls outside of the trackball which is interpreted
    * as rotation about the Z axis.
    */
   if (fNewVecZ < 0.0)
   {
      fLength = sqrt(1.0 - fNewVecZ);
      fNewVecZ  = 0.0;
      fNewVecX /= fLength;
      fNewVecY /= fLength;
//      std::cerr << "inside trackball" << std::endl;
   }
   else {
      fNewVecZ = sqrt(fNewVecZ);
   }

   /* Vector pointing from center of virtual trackball to
    * old mouse position
    */
   fOldVecX    = fOldX * 2.0 / fDiameter;
   fOldVecY    = fOldY * 2.0 / fDiameter;
   fOldVecZ    = (1.0 - fOldVecX * fOldVecX - fOldVecY * fOldVecY);

   /* If the Z component is less than 0, the mouse point
    * falls outside of the trackball which is interpreted
    * as rotation about the Z axis.
    */
   if (fOldVecZ < 0.0) {
      fLength = sqrt(1.0 - fOldVecZ);
      fOldVecZ  = 0.0;
      fOldVecX /= fLength;
      fOldVecY /= fLength;
   } else {
      fOldVecZ = sqrt(fOldVecZ);
   }

   /* Generate rotation vector by calculating cross product:
    *
    * fOldVec x fNewVec.
    *
    * The rotation vector is the axis of rotation
    * and is non-unit length since the length of a crossproduct
    * is related to the angle between fOldVec and fNewVec which we need
    * in order to perform the rotation.
    */
   *fVecX = fOldVecY * fNewVecZ - fNewVecY * fOldVecZ;
   *fVecY = fOldVecZ * fNewVecX - fNewVecZ * fOldVecX;
   *fVecZ = fOldVecX * fNewVecY - fNewVecX * fOldVecY;
}

/*******************************************************
 * void vAxisRotMatrix(float fVecX, float fVecY, float fVecZ, Matrix mNewMat)
 *
 *    Calculate the rotation matrix for rotation about an arbitrary axis.
 *
 *    The axis of rotation is specified by (fVecX,fVecY,fVecZ). The length
 *    of the vector is the amount to rotate by.
 *
 * Parameters: fVecX,fVecY,fVecZ - Axis of rotation
 *             mNewMat - Output matrix of rotation in column-major format
 *                       (ie, translation components are in column 3 on rows
 *                       0,1, and 2).
 *
 *******************************************************/
QMatrix4x4 Viewer::vAxisRotMatrix(float fVecX, float fVecY, float fVecZ) {


    float fRadians, fInvLength, fNewVecX, fNewVecY, fNewVecZ;

    /* Find the length of the vector which is the angle of rotation
     * (in radians)
     */
    fRadians = sqrt(fVecX * fVecX + fVecY * fVecY + fVecZ * fVecZ);

    /* If the vector has zero length - return the identity matrix */
    if (fRadians > -0.000001 && fRadians < 0.000001) {

        return QMatrix4x4();
    }

    /* Normalize the rotation vector now in preparation for making
     * rotation matrix.
     */
    fInvLength = 1 / fRadians;
    fNewVecX   = fVecX * fInvLength;
    fNewVecY   = fVecY * fInvLength;
    fNewVecZ   = fVecZ * fInvLength;

    /* Create the arbitrary axis rotation matrix */
    double dSinAlpha = sin(fRadians);
    double dCosAlpha = cos(fRadians);
    double dT = 1 - dCosAlpha;

    Matrix4x4 mNewMat;

    mNewMat[0][0] = dCosAlpha + fNewVecX*fNewVecX*dT;
    mNewMat[0][1] = fNewVecX*fNewVecY*dT + fNewVecZ*dSinAlpha;
    mNewMat[0][2] = fNewVecX*fNewVecZ*dT - fNewVecY*dSinAlpha;
    mNewMat[0][3] = 0;



    mNewMat[1][0] = fNewVecX*fNewVecY*dT - dSinAlpha*fNewVecZ;
    mNewMat[1][1] = dCosAlpha + fNewVecY*fNewVecY*dT;
    mNewMat[1][2] = fNewVecY*fNewVecZ*dT + dSinAlpha*fNewVecX;
    mNewMat[1][3] = 0;

    mNewMat[2][0] = fNewVecZ*fNewVecX*dT + dSinAlpha*fNewVecY;
    mNewMat[2][1] = fNewVecZ*fNewVecY*dT - dSinAlpha*fNewVecX;
    mNewMat[2][2] = dCosAlpha + fNewVecZ*fNewVecZ*dT;
    mNewMat[2][3] = 0;

    mNewMat[3][0] = 0;
    mNewMat[3][1] = 0;
    mNewMat[3][2] = 0;
    mNewMat[3][3] = 1;

    QMatrix4x4 QmNewMat = QMatrix4x4(mNewMat[0][0],mNewMat[1][0],mNewMat[2][0],mNewMat[3][0],
                                     mNewMat[0][1],mNewMat[1][1],mNewMat[2][1],mNewMat[3][1],
                                     mNewMat[0][2],mNewMat[1][2],mNewMat[2][2],mNewMat[3][2],
                                     mNewMat[0][3],mNewMat[1][3],mNewMat[2][3],mNewMat[3][3]
                                    );


    return QmNewMat;
}

void Viewer::reset_pos()
{
    modelMatrix = QMatrix4x4();
    update();
}

void Viewer::reset_ori()
{
    m_trackballRotation = QMatrix4x4();
    update();
}
