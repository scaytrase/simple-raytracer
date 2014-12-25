#include <QtGui>
#include <QApplication>
#include "raytracewindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);
    RaytraceWindow window;
    window.resize(640, 480);
    window.show();
    return app.exec();
}
