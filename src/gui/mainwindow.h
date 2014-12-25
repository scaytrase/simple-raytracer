#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "../raytracewindow.h"
#include "../textures/textureCommon.h"
#include "../materials/materialsCommon.h"
#include "../objects/objectsCommon.h"
#include "../lights/lightsCommon.h"
#include <QVector>
#include <QComboBox>
#include <QListWidgetItem>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QVector <rtTexture*> textures;
    QVector <rtMaterial*> materials;
    QVector <rtLight*> lights;
    QVector <rtObject*> objects;

    void fillTextureCombo(QComboBox *box, rtTexture *exclude = 0);
    void fillMaterialCombo(QComboBox *box);

    void addTexture(rtTexture *newTexture, QString kind = "Solid color");
    void addMaterial(rtMaterial *newMaterial);
    void addLight(rtLight *newLight);
    void addObject(rtObject *newObject, QString kind);

    void applySettings();
    void setRTWindow(RaytraceWindow *newWindow);

    void deleteTextureRef(rtTexture *texture, rtTexture *voidTexture);
    void deleteMaterialRef(rtMaterial *material, rtMaterial *voidMaterial);

private:
    Ui::MainWindow *ui;
    RaytraceWindow *rtWindow;
    rtTexture *voidTexture;

private slots:
    void on_loadButton_clicked();
    void on_saveButton_clicked();
    void on_copyMaterialButton_clicked();
    void on_copyLightButton_clicked();
    void on_copyTextureButton_clicked();
    void on_copyObjectButton_clicked();
    void on_textturesList_itemDoubleClicked(QListWidgetItem* item);
    void on_lightsList_itemDoubleClicked(QListWidgetItem* item);
    void on_materialsList_itemDoubleClicked(QListWidgetItem* item);
    void on_objectList_itemDoubleClicked(QListWidgetItem* item);
    void on_removeObjectButton_clicked();
    void on_removeLightButton_clicked();
    void on_removeMaterialButton_clicked();
    void on_removeTextureButton_clicked();
    void on_applyButton_clicked();
    void on_editObjectButton_clicked();
    void on_editLightButton_clicked();
    void on_addLightButton_clicked();
    void on_editMaterialButton_clicked();
    void on_addMaterialButton_clicked();
    void on_MainWindow_destroyed();
    void on_editTextureButton_clicked();
    void on_addTextureButton_clicked();
    void on_addObjectButton_clicked();
    void on_renderButton_clicked();
};

#endif // MAINWINDOW_H
