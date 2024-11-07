#include "mainwindow.h"
#include <QScreen>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    QRect screenrect = a.primaryScreen()->availableGeometry();
    w.move(screenrect.left(), screenrect.top());
    w.showMaximized();
    return a.exec();
}
