#include <QtGui>
#include "raytracewindow.h"
#include "gui/mainwindow.h"
#include "iostream"
#include <omp.h>

int main(int argc, char *argv[])
{
    omp_set_num_threads(25);
    omp_set_dynamic(0);
    std::cout << omp_get_num_threads() << std::endl;
    QApplication app(argc,argv);
    RaytraceWindow window;
    window.resize(1024,768);
    window.show();

    MainWindow mainWindow;
    mainWindow.setRTWindow(&window);
    mainWindow.show();

    return app.exec();
}
