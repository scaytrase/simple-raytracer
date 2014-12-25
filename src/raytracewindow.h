#ifndef RAYTRACEWINDOW_H
#define RAYTRACEWINDOW_H

#include <QWidget>
#include "rtscene.h"
#include <QKeyEvent>

class RaytraceWindow : public QWidget
{
    Q_OBJECT
public:
    bool preview;
    rtScene scene;
    explicit RaytraceWindow(QWidget *parent = 0);
    void setPreview(bool newPreview);
private:
    QImage currentImage;
    double dh,dv,distanse;
    double meantime, meancount;
    QVector< QVector <Color3> > buffer;
    QImage renderScene();
    QImage previewScene();
    void mouseMoveEvent(QMouseEvent *);
    void keyPressEvent(QKeyEvent *);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);
signals:

public slots:

};

#endif // RAYTRACEWINDOW_H
