#ifndef APPWINDOW_HPP
#define APPWINDOW_HPP

#include <QMainWindow>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <vector>
#include "Viewer.hpp"
#include "scene_lua.hpp"

class AppWindow : public QMainWindow
{
    Q_OBJECT

public:
    AppWindow(SceneNode* root);
    static Viewer* m_viewer;

private slots:
    void reset_pos();
    void reset_ori();
    void reset_joint();
    void reset_all();

    void setmode_po();
    void setmode_joint();

    void set_undo();
    void set_redo();

    void set_circle();
    void set_zbuffer();
    void set_backcull();
    void set_frontcull();

private:
    void createActions();
    void createMode();
    void createEdit();
    void createOption();
    void createMenu();

    // Each menu itself
    QMenu* m_menu_app;
    QMenu* m_menu_mode;
    QMenu* m_menu_edit;
    QMenu* m_menu_option;

    std::vector<QAction*> m_menu_actions;
    std::vector<QAction*> m_vec_modes;
    std::vector<QAction*> m_vec_edit;
    std::vector<QAction*> m_vec_option;
};

#endif
