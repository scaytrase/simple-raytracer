#ifndef OBJECTDIALOG_H
#define OBJECTDIALOG_H

#include <QDialog>
#include "../objects/objectsCommon.h"
#include "mainwindow.h"

namespace Ui {
    class objectDialog;
}

class objectDialog : public QDialog
{
    Q_OBJECT

public:
    explicit objectDialog(QWidget *parent = 0);
    ~objectDialog();

    void setObject(rtObject *newObject);
    void fillFromObject(rtObject *newObject);
    rtObject *getObject();
    QString getKind();
private:
    Ui::objectDialog *ui;
    rtObject *object;
    MainWindow *mw;

private slots:
    void on_sizeZBox_valueChanged(double );
    void on_sizeYBox_valueChanged(double );
    void on_sizeXBox_valueChanged(double );
    void on_kindBox_currentIndexChanged(int index);
};

#endif // OBJECTDIALOG_H
