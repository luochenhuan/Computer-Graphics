#include <QtWidgets>
#include <iostream>
#include "AppWindow.hpp"

// initialization
Viewer* AppWindow::m_viewer = NULL;

AppWindow::AppWindow(SceneNode *root) {
    setWindowTitle("488 Assignment Two");

    QGLFormat glFormat;
    glFormat.setVersion(3,3);
    glFormat.setProfile(QGLFormat::CoreProfile);
    glFormat.setSampleBuffers(true);

    QVBoxLayout *layout = new QVBoxLayout;
    m_viewer = new Viewer(glFormat, this);
    m_viewer->m_root = root;

    layout->addWidget(m_viewer);
    setCentralWidget(new QWidget);
    centralWidget()->setLayout(layout);

    createActions();
    createMode();
    createEdit();
    createOption();

    createMenu();
}

/**************** Application Menu *******************/
void AppWindow::createActions() {
    QAction* quitAct = new QAction(tr("&Quit"), this);
    m_menu_actions.push_back(quitAct);
    // We set the accelerator keys
    // Alternatively, you could use: setShortcuts(Qt::CTRL + Qt::Key_P);
    quitAct->setShortcuts(QKeySequence::Quit);
    // Set the tip
    quitAct->setStatusTip(tr("Exits the file"));
    // Connect the action with the signal and slot designated
    connect(quitAct, SIGNAL(triggered()), this, SLOT(close()));

    QAction* reset_posAct = new QAction(tr("&Reset Positon"), this);
    m_menu_actions.push_back(reset_posAct);
    reset_posAct->setShortcut(Qt::Key_I);
    reset_posAct->setStatusTip(tr("reset_posAct"));
    connect(reset_posAct, SIGNAL(triggered()), this, SLOT(reset_pos()));

    QAction* reset_OriAct = new QAction(tr("&Reset Orientation"), this);
    m_menu_actions.push_back(reset_OriAct);
    reset_OriAct->setShortcut(Qt::Key_O);
    reset_OriAct->setStatusTip(tr("reset_OriAct"));
    connect(reset_OriAct, SIGNAL(triggered()), this, SLOT(reset_ori()));

    QAction* reset_jointAct = new QAction(tr("&Reset Joints"), this);
    m_menu_actions.push_back(reset_jointAct);
    reset_jointAct->setShortcut(Qt::Key_N);
    reset_jointAct->setStatusTip(tr("reset_joint"));
    connect(reset_jointAct, SIGNAL(triggered()), this, SLOT(reset_joint()));

    QAction* reset_allAct = new QAction(tr("&Reset All"), this);
    m_menu_actions.push_back(reset_allAct);
    reset_allAct->setShortcut(Qt::Key_A);
    reset_allAct->setStatusTip(tr("reset_allAct"));
    connect(reset_allAct, SIGNAL(triggered()), this, SLOT(reset_all()));
}

/**************** Mode Menu *******************/
void AppWindow::createMode()
{
    QAction* poMode = new QAction(tr("&Position/Orientation"), this);
    m_vec_modes.push_back(poMode);
    poMode->setShortcut(Qt::Key_P);
    poMode->setStatusTip(tr("Position/Orientation"));
    connect(poMode, SIGNAL(triggered()), this, SLOT(setmode_po()));

    QAction* jointMode = new QAction(tr("&Joints"), this);
    m_vec_modes.push_back(jointMode);
    jointMode->setShortcut(Qt::Key_J);
    jointMode->setStatusTip(tr("Joints"));
    connect(jointMode, SIGNAL(triggered()), this, SLOT(setmode_joint()));

    /**** group mode choices *****/
    poMode->setCheckable(true);
    jointMode->setCheckable(true);

    QActionGroup* mode_group = new QActionGroup(this);
    poMode->setActionGroup(mode_group);
    jointMode->setActionGroup(mode_group);

    poMode->toggle();
}

/**************** Edit Menu *******************/
void AppWindow::createEdit()
{
    QAction* undo = new QAction(tr("&Undo"), this);
    m_vec_edit.push_back(undo);
    undo->setShortcut(Qt::Key_U);
    undo->setStatusTip(tr("Undo"));
    connect(undo, SIGNAL(triggered()), this, SLOT(set_undo()));

    QAction* redo = new QAction(tr("&Redo"), this);
    m_vec_edit.push_back(redo);
    redo->setShortcut(Qt::Key_R);
    redo->setStatusTip(tr("redo"));
    connect(redo, SIGNAL(triggered()), this, SLOT(set_redo()));
}
/**************** Option Menu *******************/

void AppWindow::createOption()
{
    QAction* circle_op = new QAction(tr("&Circle"), this);
    m_vec_option.push_back(circle_op);
    circle_op->setShortcut(Qt::Key_C);
    circle_op->setStatusTip(tr("Circle"));
    connect(circle_op, SIGNAL(triggered()), this, SLOT(set_circle()));

    QAction* zbuffer_op = new QAction(tr("&Z-buffer"), this);
    m_vec_option.push_back(zbuffer_op);
    zbuffer_op->setShortcut(Qt::Key_Z);
    zbuffer_op->setStatusTip(tr("Z-buffer"));
    connect(zbuffer_op, SIGNAL(triggered()), this, SLOT(set_zbuffer()));

    QAction* back_op = new QAction(tr("&Backface cull"), this);
    m_vec_option.push_back(back_op);
    back_op->setShortcut(Qt::Key_B);
    back_op->setStatusTip(tr("Backface cull"));
    connect(back_op, SIGNAL(triggered()), this, SLOT(set_backcull()));

    QAction* front_op = new QAction(tr("&Frontface cull"), this);
    m_vec_option.push_back(front_op);
    front_op->setShortcut(Qt::Key_F);
    front_op->setStatusTip(tr("Frontface cull"));
    connect(front_op, SIGNAL(triggered()), this, SLOT(set_frontcull()));

    circle_op->setCheckable(true);
    zbuffer_op->setCheckable(true);
    back_op->setCheckable(true);
    front_op->setCheckable(true);

}


void AppWindow::createMenu() {
    m_menu_app = menuBar()->addMenu(tr("&Application"));
    for (auto& action : m_menu_actions) {
        m_menu_app->addAction(action);
    }

    m_menu_mode = menuBar()->addMenu(tr("&Mode"));
    for (auto& action : m_vec_modes) {
        m_menu_mode->addAction(action);
    }

    m_menu_edit = menuBar()->addMenu(tr("&Edit"));
    for (auto& action : m_vec_edit) {
        m_menu_edit->addAction(action);
    }

    m_menu_option = menuBar()->addMenu(tr("&Option"));
    for (auto& action : m_vec_option) {
        m_menu_option->addAction(action);
    }
}


void AppWindow::reset_pos()
{
    m_viewer->reset_pos();
}
void AppWindow:: reset_ori()
{
    m_viewer->reset_ori();
}
void AppWindow:: reset_joint()
{

}
void AppWindow:: reset_all()
{
    m_viewer->reset();
}
void AppWindow:: setmode_po()
{
    m_viewer->setMode(Viewer::POS_ORI);
}
void AppWindow:: setmode_joint()
{
    m_viewer->setMode(Viewer::JOINTS);
}

void AppWindow:: set_undo()
{

}
void AppWindow:: set_redo()
{

}

void AppWindow::set_circle()
{
    m_viewer->setDrawCircle() ;
}

void AppWindow::set_zbuffer()
{
    m_viewer->set_zbuffer() ;
}

void AppWindow::set_backcull()
{
    m_viewer->set_backcull() ;
}

void AppWindow::set_frontcull()
{
    m_viewer->set_frontcull() ;

}
