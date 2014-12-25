#include "raytracewindow.h"

#include <QPainter>
#include <QTimer>
#include <QDateTime>

RaytraceWindow::RaytraceWindow(QWidget *parent) :
        QWidget(parent) {
    dh = 1;
    dv = pi / 2 - pi / 10;
    distanse = 600;
    vertex3f observerPosition(
            distanse * qSin(dh) * qSin(dv),
            distanse * qCos(dh) * qSin(dv),
            distanse * qCos(dv)
    );

    scene.setObserver(observerPosition);
    preview = true;

}

void  RaytraceWindow::keyPressEvent(QKeyEvent *newevent) {
    if (newevent->key() == Qt::Key_Space) {
        setPreview(!preview);
        return;
    }

    else if (newevent->key() == Qt::Key_Escape) {
        exit(0);
    }
    if (preview) {
        switch (newevent->key()) {
            case Qt::Key_W:
                dv -= 0.15;
                break;
            case Qt::Key_A:
                dh += 0.15;
                break;
            case Qt::Key_D:
                dh -= 0.15;
                break;
            case Qt::Key_S:
                dv += 0.15;
                break;
            case Qt::Key_Q:
                distanse -= 10;
                break;
            case Qt::Key_E:
                distanse += 10;
                break;
            case Qt::Key_R:
                distanse = 600;
                break;
            case Qt::Key_Z:
                dh -= 0.01;
                break;
            case Qt::Key_C:
                dv += 0.01;
                break;

            default:
                break;
        }
        vertex3f newObserverPosition(
                distanse * qSin(dh) * qSin(dv),
                distanse * qCos(dh) * qSin(dv),
                distanse * qCos(dv)
        );

        scene.setObserver(newObserverPosition);
    }
    if (newevent->key() == Qt::Key_U)
        std::cout << (currentImage.save("output.png", "png", 100) ? "Image saved" : "Image not saved") << std::endl;

    update();
}

void RaytraceWindow::paintEvent(QPaintEvent *) {
    QPainter p(this);
    //currentImage = preview ? previewScene() : renderScene();
    if (preview) currentImage = scene.getImage(width(), height(), true);
    p.drawImage(0, 0, currentImage);
    return;
}

void RaytraceWindow::resizeEvent(QResizeEvent *) {
}

void RaytraceWindow::mouseMoveEvent(QMouseEvent *) {

}

void RaytraceWindow::setPreview(bool newPreview) {
    preview = newPreview;
    if (!preview) currentImage = scene.getImage(width(), height(), false);
    update();
}
