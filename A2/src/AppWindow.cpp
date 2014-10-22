/***************************************************/
// <author> Haiyu Zhen
// <UserID> h2zhen
// <Student Num> 20552637
// <Email> h2zhen@uwaterloo.ca
// CS 688: Computer Graphics Assignment 2
// <date>  Oct. 2014
/***************************************************/
#include <QtWidgets>
#include <iostream>
#include "AppWindow.hpp"

AppWindow::AppWindow() {
    setWindowTitle("488 Assignment Two");

    QGLFormat glFormat;
    glFormat.setVersion(3,3);
    glFormat.setProfile(QGLFormat::CoreProfile);
    glFormat.setSampleBuffers(true);

    QVBoxLayout *layout = new QVBoxLayout;
    // m_menubar = new QMenuBar;
    m_viewer = new Viewer(glFormat, this);
    layout->addWidget(m_viewer);
    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);

    createActions();
    createMenu();
    createStatusbar();

    tickTimer = new QTimer(this);
    connect(tickTimer, SIGNAL(timeout()), this, SLOT(setlabel()));
    tickTimer->start(10);
}

/*************************Key Press*********************************/
void AppWindow::keyPressEvent(QKeyEvent *event) {
    if (event->key() == Qt::Key_A) {
        reset();
    }
    if (event->key() == Qt::Key_O) {
        setmode_vr();
    }
    if (event->key() == Qt::Key_N) {
        setmode_vt();
    }
    if (event->key() == Qt::Key_P) {
        setmode_pers();
      }
    if (event->key() == Qt::Key_R) {
        setmode_mr();
      }
    if (event->key() == Qt::Key_T) {
        setmode_mt();
      }
    if (event->key() == Qt::Key_S) {
        setmode_scale();
      }
    if (event->key() == Qt::Key_V) {
        setmode_vp();
      }
}


/*************************Action Creation*********************************/

void AppWindow::createActions() {
    // Creates a new action for quiting and pushes it onto the menu actions vector
    QAction* quitAct = new QAction(tr("&Quit"), this);
    m_menu_actions.push_back(quitAct);

    // We set the accelerator keys
    // Alternatively, you could use: setShortcuts(Qt::CTRL + Qt::Key_P);
    quitAct->setShortcuts(QKeySequence::Quit);

    // Set the tip
    quitAct->setStatusTip(tr("Exits the file"));

    // Connect the action with the signal and slot designated
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    resetAct = new QAction(tr("&Reset"), this);
    m_menu_actions.push_back(resetAct);

    resetAct->setShortcut(Qt::Key_A);
    connect(resetAct, SIGNAL(triggered()), this, SLOT(reset()));

    m_menu_actions.push_back(resetAct);

    /**************** Interaction View Mode Actions *******************/

    // view rotate mode
    vrAct = new QAction(tr("&View Rotate"), this);
    m_vec_modes.push_back(vrAct);

    vrAct->setShortcut(Qt::Key_O);
    connect(vrAct, SIGNAL(triggered()), this, SLOT(setmode_vr()));


    // view translate mode
    vtAct = new QAction(tr("&View Translate"), this);
    m_vec_modes.push_back(vtAct);

    vtAct->setShortcut(Qt::Key_N);
    connect(vtAct, SIGNAL(triggered()), this, SLOT(setmode_vt()));


    // view pers mode
    persAct = new QAction(tr("&Perspective"), this);
    m_vec_modes.push_back(persAct);

    persAct->setShortcut(Qt::Key_P);
    connect(persAct, SIGNAL(triggered()), this, SLOT(setmode_pers()));

    /**************** Interaction Model Mode Actions *******************/

    // model rotate mode
    mrAct = new QAction(tr("&Model Rotate"), this);
    m_vec_modes.push_back(mrAct);

    mrAct->setShortcut(Qt::Key_R);
    connect(mrAct, SIGNAL(triggered()), this, SLOT(setmode_mr()));


    // model translate mode
    mtAct = new QAction(tr("&Model Translate"), this);
    m_vec_modes.push_back(mtAct);

    mtAct->setShortcut(Qt::Key_T);
    connect(mtAct, SIGNAL(triggered()), this, SLOT(setmode_mt()));


    // scale mode
    scaleAct = new QAction(tr("&Scale"), this);
    m_vec_modes.push_back(scaleAct);

    scaleAct->setShortcut(Qt::Key_S);
    connect(scaleAct, SIGNAL(triggered()), this, SLOT(setmode_scale()));

    // viewport mode
    viewportAct = new QAction(tr("&Viewport"), this);
    m_vec_modes.push_back(viewportAct);

    viewportAct->setShortcut(QKeySequence(Qt::Key_V));
    connect(viewportAct, SIGNAL(triggered()), this, SLOT(setmode_vp()));

    /**** group view mode choices *****/
    vrAct->setCheckable(true);
    vtAct->setCheckable(true);
    persAct->setCheckable(true);
    mrAct->setCheckable(true);
    mtAct->setCheckable(true);
    scaleAct->setCheckable(true);
    viewportAct->setCheckable(true);

    QActionGroup* vi_group = new QActionGroup(this);
    vrAct->setActionGroup(vi_group);
    vtAct->setActionGroup(vi_group);
    persAct->setActionGroup(vi_group);

    mrAct->setActionGroup(vi_group);
    mtAct->setActionGroup(vi_group);
    scaleAct->setActionGroup(vi_group);
    viewportAct->setActionGroup(vi_group);

    mrAct->toggle();
}

void AppWindow::createMenu() {
    m_menu_app = menuBar()->addMenu(tr("&Application"));
    m_menu_mode = menuBar()->addMenu(tr("&Mode"));
    for (auto& action : m_menu_actions) {
        m_menu_app->addAction(action);
    }

    for (auto& action : m_vec_modes) {
        m_menu_mode->addAction(action);
    }
}

void AppWindow::createStatusbar()
{
    statusBar() -> addWidget(m_label);

    const char* cstr = m_viewer->label_text();
    m_label -> setText(cstr);
}

void AppWindow::reset(){
    m_viewer->reset_view();
    const char* cstr = m_viewer->label_text();
    m_label -> setText(cstr);
}

void AppWindow::setmode_vr(){
    m_viewer->set_mode(Viewer::VIEW_ROT);
    vrAct->setChecked(true);

    const char* cstr = m_viewer->label_text();
    m_label -> setText(cstr);
}
void AppWindow::setmode_mr(){
    m_viewer->set_mode(Viewer::MODEL_ROT);
    mrAct->setChecked(true);

    const char* cstr = m_viewer->label_text();
    m_label -> setText(cstr);
}
void AppWindow::setmode_vt(){
    m_viewer->set_mode(Viewer::VIEW_TRANS);
    vtAct->setChecked(true);

    const char* cstr = m_viewer->label_text();
    m_label -> setText(cstr);
}
void AppWindow::setmode_mt(){
    m_viewer->set_mode(Viewer::MODEL_TRANS);
    mtAct->setChecked(true);

    const char* cstr = m_viewer->label_text();
    m_label -> setText(cstr);
}
void AppWindow::setmode_pers(){
    m_viewer->set_mode(Viewer::VIEW_PERS);
    persAct->setChecked(true);

    const char* cstr = m_viewer->label_text();
    m_label -> setText(cstr);
}
void AppWindow::setmode_scale(){
    m_viewer->set_mode(Viewer::MODEL_SCALE);
    scaleAct->setChecked(true);

    const char* cstr = m_viewer->label_text();
    m_label -> setText(cstr);
}
void AppWindow::setmode_vp(){
    m_viewer->set_mode(Viewer::VIEWPORT);
    viewportAct->setChecked(true);

    const char* cstr = m_viewer->label_text();
    m_label -> setText(cstr);
}

void AppWindow::setlabel() {
    const char* cstr = m_viewer->label_text();
    m_label -> setText(cstr);
}


