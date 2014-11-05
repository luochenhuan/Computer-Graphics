/***************************************************/
// <author> Haiyu Zhen
// <UserID> h2zhen
// <Student Num> 20552637
// <Email> h2zhen@uwaterloo.ca
// CS 688: Computer Graphics Assignment 2
// <date>  Oct. 2014
/***************************************************/
#ifndef APPWINDOW_HPP
#define APPWINDOW_HPP

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <vector>
#include "Viewer.hpp"
#include <QLabel>

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppWindow();

protected:
    void keyPressEvent(QKeyEvent *event);

private slots:
    void reset();
    void setmode_vr();
    void setmode_mr();
    void setmode_vt();
    void setmode_mt();
    void setmode_pers();
    void setmode_scale();
    void setmode_vp();
    void setlabel();

private:
    void createActions();
    void createMenu();
    void createStatusbar();

    // Each menu itself
    QMenu* m_menu_app;
    QMenu* m_menu_mode;

    std::vector<QAction*> m_menu_actions;
    std::vector<QAction*> m_vec_modes;

    QAction* resetAct;
    QAction* vrAct;
    QAction* vtAct;
    QAction* persAct;
    QAction* mrAct;
    QAction* mtAct;
    QAction* scaleAct;
    QAction* viewportAct;

    Viewer* m_viewer;

    QLabel* m_label=new QLabel("text");

    QTimer* tickTimer;
};

#endif
