#ifndef MATERIALDIALOG_H
#define MATERIALDIALOG_H

#include <QDialog>
#include "mainwindow.h"
#include "../materials/materialsCommon.h"

namespace Ui {
    class materialDialog;
}

class materialDialog : public QDialog
{
    Q_OBJECT

public:
    explicit materialDialog(QWidget *parent = 0);
    ~materialDialog();

    void fillTextureCombos();
    rtMaterial *getMaterial();
    void setMaterial(rtMaterial *newMaterial);
    void fillFromMaterial(rtMaterial *material);
private:
    Ui::materialDialog *ui;
    MainWindow *mw;
    rtMaterial *material;
};

#endif // MATERIALDIALOG_H
