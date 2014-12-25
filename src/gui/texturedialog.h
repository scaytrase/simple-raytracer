#ifndef TEXTUREDIALOG_H
#define TEXTUREDIALOG_H

#include <QDialog>
#include <typeinfo>
#include "../textures/textureCommon.h"
#include "mainwindow.h"

namespace Ui {
    class textureDialog;
}

class textureDialog : public QDialog
{
    Q_OBJECT

public:
    rtTexture *getTexture();
    void setTexture(rtTexture *newTexture);
    void fillFromTexture(rtTexture *texture);
    QString getKind();

    explicit textureDialog(QWidget *parent = 0);
    ~textureDialog();

private:
    rtTexture *texture;
    Ui::textureDialog *ui;
    MainWindow *mw;
    void fill_combos();

private slots:
    void on_mapSelectImageButton_clicked();
    void on_selectImageButton_clicked();
    void on_redColorBox_valueChanged(int );
    void on_kindBox_currentIndexChanged(int index);
};

#endif // TEXTUREDIALOG_H
