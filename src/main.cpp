#include <QtGui>
#include <QApplication>
#include "raytracewindow.h"
//#include <omp.h>

int main(int argc, char *argv[])
{
    //omp_set_num_threads(25);
    //omp_set_dynamic(0);
    QApplication app(argc,argv);
    RaytraceWindow window;
    window.resize(640,480);
    window.show();
    return app.exec();
}
