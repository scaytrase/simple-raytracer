#ifndef LIGHTDIALOG_H
#define LIGHTDIALOG_H

#include <QDialog>
#include "../lights/lightsCommon.h"

namespace Ui {
    class lightDialog;
}

class lightDialog : public QDialog
{
    Q_OBJECT

public:
    explicit lightDialog(QWidget *parent = 0);
    ~lightDialog();

    rtLight *getLight();
    void setLight(rtLight *newLight);
    void fillFromLight(rtLight *light);

private:
    Ui::lightDialog *ui;
    rtLight *light;
};

#endif // LIGHTDIALOG_H
