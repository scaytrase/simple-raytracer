#include "raytracewindow.h"

#include <QPainter>
#include <iostream>
#include <QTimer>
#include <QDateTime>
#include <QImage>
#include <omp.h>
#include <QMessageBox>
RaytraceWindow::RaytraceWindow(QWidget *parent) :
        QWidget(parent)
{
    dh = 1;
    dv = pi/2-pi/10;
    distanse = 380;
    vertex3d observerPosition(
            distanse*qSin(dh)*qSin(dv),
            distanse*qCos(dh)*qSin(dv),
            distanse*qCos(dv)
            );

    scene.setObserver(observerPosition);
    preview = true;

}

void  RaytraceWindow::keyPressEvent(QKeyEvent * newevent){
	if (newevent->key() == Qt::Key_Space) {
		setPreview(!preview);
	}

	else if (newevent->key() == Qt::Key_Escape) {
		close();
	}
	if (preview)
	{
		switch (newevent->key()){
		case Qt::Key_W:
			dv -= 0.05;
			break;
		case Qt::Key_A:
			dh += 0.05;
			break;
		case Qt::Key_D:
			dh -= 0.05;
			break;
		case Qt::Key_S:
			dv += 0.05;
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

		}
		vertex3d newObserverPosition(
				distanse*qSin(dh)*qSin(dv),
				distanse*qCos(dh)*qSin(dv),
				distanse*qCos(dv)
				);

		scene.setObserver(newObserverPosition);
	}
	if (newevent->key() ==  Qt::Key_U)
		std::cout << (currentImage.save("output.png","png",100) ? "Image saved" : "Image not saved") << std::endl;

	update();
}

void RaytraceWindow::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    //currentImage = preview ? previewScene() : renderScene();
    if (preview) currentImage = previewScene();
    p.drawImage(0,0,currentImage);
    return;
}

QImage RaytraceWindow::renderScene()
{
    int H = height(), W = width();

    vertex3d
            screenpos =  scene.spot_pos - scene.observer_pos,
            dx(screenpos.y(),-screenpos.x(),0),
            dy = dx[screenpos];

    dy = dy / !dy;
    dx = dx / !dx;
    double dist = !screenpos;
    double scale = 1.0/qMin(H,W);
    double AxisNormValue =  dist*(1 - qCos(pi/6.0));
    dx = dx * AxisNormValue * scale;
    dy = dy * AxisNormValue * scale;
    Color3 result;

    QTime timer1;
    timer1.start();
    QString title;
    int k=1;
    rayd newray;
    newray.point = scene.observer_pos;
    QRgb * pixels = (QRgb *) malloc(sizeof(QRgb)*W*H);

    for (int x = 0; x < W; x++){
#pragma omp parallel for firstprivate(newray,x,pixels) private(result)  num_threads(16)
        for (int y = 0; y < H; y++)
        {
            newray.direction =
                    screenpos -
                    dy*( y - H / 2) /*/qCos((y-H/2)/H) */-
                    dx*( x - W / 2) /*/qCos((x-W/2)/W)*/;
            result = scene.sendRay(newray,0);
            pixels [y*W + x] =
                    ( int(255*result.r) << 16) |
                    ( int(255*result.g) << 8 ) |
                      int(255*result.b)
                    ;
        }
        title.sprintf("%d %%- %.2f sec for %dx%d",int(100*k/W), timer1.elapsed()/1000.0, width(), height());
        setWindowTitle(title);
        k++;
    }
    title.sprintf("%.2f sec", timer1.elapsed()/1000.0);
    setWindowTitle(title);

    return QImage((uchar*)pixels, W,H,QImage::Format_RGB32).scaled(width(),height(),Qt::IgnoreAspectRatio,Qt::SmoothTransformation);
}

QImage RaytraceWindow::previewScene()
{
    int render_step = 3;
    int H = height()/render_step, W = width()/render_step;

    vertex3d
            screenpos =  scene.spot_pos - scene.observer_pos,
            dx(screenpos.y(),-screenpos.x(),0),
            dy = dx[screenpos];

    dy = dy / !dy;
    dx = dx / !dx;
    double dist = !screenpos;
    double scale = 1.0/qMin(H,W);
    double AxisNormValue =  dist*(1 - qCos(pi/6.0));
    dx = dx * AxisNormValue * scale;
    dy = dy * AxisNormValue * scale;

    QTime timer1;
    timer1.start();
    QString title;
    int k=1;

    Color3 result;
    rayd newray;
    newray.point = scene.observer_pos;
        QRgb * pixels = (QRgb *) malloc(sizeof(QRgb)*W*H);
    for (int x = 0; x < W; x ++){
#pragma omp parallel for firstprivate(newray,x) private(result)
        for (int y = 0; y < H; y ++)
        {
            newray.direction =
                    screenpos -
                    dy*( y - H / 2) -
                    dx*( x - W / 2) ;
            result = scene.sendPreviewRay(newray);
            pixels [y*W + x] =
                    ( int(255*result.r) << 16) |
                    ( int(255*result.g) << 8 ) |
                      int(255*result.b)
                    ;
        }
        title.sprintf("%d %%- %.2f sec for %dx%d",int(100*k/W), timer1.elapsed()/1000.0, width(), height());
        setWindowTitle(title);
        k++;
    }

    return QImage((uchar*)pixels, W,H,QImage::Format_RGB32).scaled(width(),height());

}

void RaytraceWindow::resizeEvent(QResizeEvent *)
{
}

void RaytraceWindow::mouseMoveEvent(QMouseEvent * )
{

}
void RaytraceWindow::setPreview(bool newPreview)
{
    preview = newPreview;
    if (!preview) currentImage = renderScene();
    update();
}
