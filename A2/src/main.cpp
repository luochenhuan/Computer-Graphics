/***************************************************/
// <author> Haiyu Zhen
// <UserID> h2zhen
// <Student Num> 20552637
// <Email> h2zhen@uwaterloo.ca
// CS 688: Computer Graphics Assignment 2
// <date>  Oct. 2014
/***************************************************/
#include <QApplication>
#include <QDesktopWidget>
#include "AppWindow.hpp"

int main(int argc, char** argv)
{
    QApplication app(argc, argv);

    AppWindow window;
    window.resize(window.sizeHint());
    int desktopArea = QApplication::desktop()->width() * 
                      QApplication::desktop()->height();

    int widgetArea = window.width() * window.height();

    if (((float)widgetArea / (float) desktopArea) < 0.75f) {
        window.show();
    } else {
        window.showMaximized();
    }

    return app.exec();
}

