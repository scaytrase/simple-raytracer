#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QDialog>
#include "objectdialog.h"
#include "lightdialog.h"
#include "texturedialog.h"
#include "materialdialog.h"
#include "../utils/color3.h"
#include <QMessageBox>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) :
        QMainWindow(parent),
        ui(new Ui::MainWindow)
{
    ui->setupUi(this);

	// set default objects
	voidTexture = new rtSolidColorTexture(colorBlack, "(void)");
	rtTexture *blackTexture = new rtSolidColorTexture(colorBlack, "(black)");
	rtTexture *whiteTexture = new rtSolidColorTexture(colorWhite, "(white)");
	rtTexture *redTexture = new rtSolidColorTexture(colorRed, "(red)");
	rtTexture *lightGrayTexture = new rtSolidColorTexture(colorLightGray, "(light gray)");
	rtTexture *darkGrayTexture = new rtSolidColorTexture(colorDarkGray, "(dark gray)");
	rtTexture *yellowTexture = new rtSolidColorTexture(colorYellow, "(yellow)");
	rtTexture *orangeTexture = new rtSolidColorTexture(colorOrange, "(orange)");
	rtTexture *greenTexture = new rtSolidColorTexture(colorGreen, "(green)");
	rtTexture *blueTexture = new rtSolidColorTexture(colorBlue, "(blue)");
	rtTexture *magentaTexture = new rtSolidColorTexture(colorRed + colorBlue, "(Magenta)");
	rtTexture *cyanTexture = new rtSolidColorTexture(colorBlue + colorGreen, "(Cyan)");

    rtImageTexture * checkerTexture   = new rtImageTexture("textures/checker.png");
    rtImageTexture * checkerNormalMap = new rtNormalMap("textures/plitka.png",false);
    rtImageTexture * checkerTexture2  = new rtImageTexture("textures/plitka.png");

    rtImageTexture * brickNormal = new rtNormalMap("textures/brick.png",false);
    rtImageTexture * brick  = new rtImageTexture("textures/brick.png");

    rtImageTexture * checkerTextureN  = new rtNormalMap("textures/checker.png",true);
    rtImageTexture * snowTextureN  = new rtNormalMap("textures/noise.png",false);
    checkerTexture->setTile(4,4);
    checkerTexture->setName("checker 4");
    checkerTextureN->setTile(4,4);
    checkerTextureN->setName("checker 4 Normal");
    checkerTexture2->setTile(0.05,0.05);
    checkerTexture2->setName("checker 0.25");
    checkerNormalMap->setTile(0.05,0.05);
    checkerNormalMap->setName("checker 0.25 Normal");
    snowTextureN->setTile(10,10);
    snowTextureN->setName("snow 1 normal");
    brick->setName("brick map");
    brick->setTile(10,10);
    brickNormal->setName("brick map normal");
    brickNormal->setTile(10,10);

    rtMaterial
            * planeMat = new rtMaterial(checkerTexture2,blackTexture,whiteTexture,lightGrayTexture,blackTexture),
            * sphereMat1 = new rtMaterial(magentaTexture,blackTexture,whiteTexture,lightGrayTexture,blackTexture,2,5),
            * sphereMat2 = new rtMaterial(yellowTexture,blackTexture,whiteTexture,lightGrayTexture,blackTexture,2,5),
            * sphereMat3 = new rtMaterial(cyanTexture,blackTexture,whiteTexture,lightGrayTexture,blackTexture,2,5),
            * sphereMat4 = new rtMaterial(greenTexture,blackTexture,whiteTexture,lightGrayTexture,blackTexture,2,5),
            * sphereMat5 = new rtMaterial(redTexture,blackTexture,whiteTexture,lightGrayTexture,blackTexture,2,5),
            * glassMat = new rtMaterial(lightGrayTexture,blackTexture,whiteTexture,blackTexture,lightGrayTexture,1,5),
            * baseMat = new rtMaterial(brick,blackTexture,whiteTexture,blackTexture,blackTexture,2,25),
            * snowMat = new rtMaterial(whiteTexture,darkGrayTexture,whiteTexture,blackTexture,blackTexture,2,10),
            * vedroMat = new rtMaterial(lightGrayTexture,blackTexture,whiteTexture,darkGrayTexture,blackTexture,2,20),
            * leafmat = new rtMaterial(greenTexture,darkGrayTexture,whiteTexture,darkGrayTexture,blackTexture,2,20),
            * trunkmat = new rtMaterial(orangeTexture,darkGrayTexture,whiteTexture,darkGrayTexture,blackTexture,2,20),
            * noseMat = new rtMaterial(redTexture,darkGrayTexture,whiteTexture,blackTexture,blackTexture,2,20);

    planeMat->setName("planeMat");
    planeMat->setBump(1,checkerNormalMap);
    baseMat->setBump(1,brickNormal);
    sphereMat1->setName("SphereMat1");
    sphereMat2->setName("SphereMat2");
    sphereMat3->setName("SphereMat3");
    sphereMat4->setName("SphereMat4");
    sphereMat5->setName("SphereMat5");
    snowMat->setName("Snow");
    noseMat->setName("Nose");
    vedroMat->setName("vedroMat");
    leafmat->setName("leafmat");
    trunkmat->setName("trunkmat");
    glassMat->setName("glass");
    baseMat->setName("base");
    snowMat->setBump(1,snowTextureN);

    addTexture(voidTexture);
    addTexture(whiteTexture);
    addTexture(redTexture);
    addTexture(blueTexture);
    addTexture(lightGrayTexture);
    addTexture(magentaTexture);
    addTexture(blackTexture);
    addTexture(darkGrayTexture);
    addTexture(yellowTexture);
    addTexture(orangeTexture);
    addTexture(greenTexture);
    addTexture(blueTexture);
    addTexture(magentaTexture);
    addTexture(cyanTexture);
    addTexture(checkerNormalMap, "Normal map");
    addTexture(checkerTexture, "Image texture");
    addTexture(checkerTexture2, "Image texture");
    addTexture(checkerTextureN, "Normal map");
    addTexture(snowTextureN, "Normal map");
    addMaterial(planeMat);
    addMaterial(noseMat);
    addMaterial(leafmat);
    addMaterial(trunkmat);
    addMaterial(snowMat);
    addMaterial(vedroMat);
    addMaterial(glassMat);
    addMaterial(baseMat);
    addMaterial(sphereMat1);
    addMaterial(sphereMat2);
    addMaterial(sphereMat3);
    addMaterial(sphereMat4);
    addMaterial(sphereMat5);

    rtPlaneObject  * plane1 = new rtPlaneObject(vertex3d(0,0,-14));
    plane1->setName("Floor");
    plane1->setMaterial(planeMat);
    plane1->setMappingMode(rtPlanarMap);
    rtSphereObject * sm_bot = new rtSphereObject(vertex3d(0,0,4),6);
    sm_bot->setName("sm_bottom");
    sm_bot->setMaterial(snowMat);
    rtSphereObject * sm_mid = new rtSphereObject(vertex3d(0,0,11),5);
    sm_mid->setName("sm_middle");
    sm_mid->setMaterial(snowMat);
    rtSphereObject * sm_top = new rtSphereObject(vertex3d(0,0,17),4);
    sm_top->setName("sm_top");
    sm_top->setMaterial(snowMat);
    rtConeObject * sm_nose = new rtConeObject ( vertex3d(3,0,17),5,0,vertex3d(3,3,3));
    sm_nose->setName("sm_nose");
    sm_nose->setMaterial(noseMat);
    sm_nose->setRotation(vertex3d(0,-1,0)/2);
    rtConeObject * sm_vedro = new rtConeObject ( vertex3d(0,0,19),8,4,vertex3d(3.5,3.5,1));
    sm_vedro->setName("sm_vedro");
    sm_vedro->setMaterial(vedroMat);
//    sm_vedro->setRotation(vertex3d(0.1,0.4,0)/10);
    addObject(sm_bot, "Sphere");
    addObject(sm_mid, "Sphere");
    addObject(sm_top, "Sphere");
    addObject(sm_nose, "Cone");
    addObject(sm_vedro, "Cone");

    for (int i=0; i< 11; i++)
    {
        float nx,ny,nz,ns,n1x,n1y;
        ny = 15 - ((qrand()*qrand())%300)/10.0;
        nx = 15 - ((qrand()*qrand())%300)/10.0;
        n1x = nx/25.0;
        n1y = ny/25.0;
        nz = -(15*qSqrt(1 - n1x*n1x+n1y*n1y) - 15) - 1;
        ns = 2 + ((qrand()*qrand())%30)/10.0;
        rtSphereObject * snball1 = new rtSphereObject(vertex3d(nx,ny,0+nz),ns);
        snball1->setName("snowball1");
        snball1->setMaterial(snowMat);
        addObject(snball1, "Sphere");
    }

    for (int i=0; i< 3; i++)
    {
        float nx,ny,nz,ns,n1x,n1y;
        ny = 15 - ((qrand()*qrand())%3000)/100.0;
        nx = 15 - ((qrand()*qrand())%3000)/100.0;
        n1x = (nx+2)/25.0;
        n1y = (ny+2)/25.0;
        nz = -(15*qSqrt(1 - n1x*n1x+n1y*n1y) - 15) - 2;
        ns = 0.5 + ((qrand()*qrand())%1000)/1000.0;
        rtCylinderObject * trunk = new rtCylinderObject(vertex3d(nx,ny,0+nz),vertex3d(2*ns,2*ns,1),3*ns);
        trunk->setName("trunk");
        trunk->setMaterial(trunkmat);
        addObject(trunk, "Cylinder");
        rtConeObject * leaf1 = new  rtConeObject(vertex3d(nx,ny,3*ns+nz),4*ns,2*ns,vertex3d(4*ns,4*ns,1));
        leaf1->setName("leaf1");
        leaf1->setMaterial(leafmat);
        addObject(leaf1, "Cone");
        rtConeObject * leaf2 = new  rtConeObject(vertex3d(nx,ny,2*3*ns -ns+nz),4*ns,1*ns,vertex3d(3*ns,3*ns,1));
        leaf2->setName("leaf1");
        leaf2->setMaterial(leafmat);
        addObject(leaf2, "Cone");
        rtConeObject * leaf3 = new  rtConeObject(vertex3d(nx,ny,3*3*ns - 2*ns+nz),4*ns,0,vertex3d(2*ns,2*ns,1));
        leaf3->setName("leaf1");
        leaf3->setMaterial(leafmat);
        addObject(leaf3, "Cone");
    }

    rtSphereObject * toyBall = new rtSphereObject(vertex3d(0,0,1),25);
    toyBall->setName("glass");
    toyBall->setMaterial(glassMat);
    addObject(toyBall,"Sphere");

//    rtSphereObject * ball1 = new rtSphereObject(vertex3d(-30,-30,1),15);
//    ball1->setName("glass");
//    ball1->setMaterial(sphereMat1);
//    addObject(ball1,"Sphere");
    rtSphereObject * ball2 = new rtSphereObject(vertex3d(-30,30,1),15);
    ball2->setName("glass");
    ball2->setMaterial(sphereMat2);
    addObject(ball2,"Sphere");
//    rtSphereObject * ball3 = new rtSphereObject(vertex3d(0,-60,1),15);
//    ball3 ->setName("glass");
//    ball3 ->setMaterial(sphereMat3);
//    addObject(ball3 ,"Sphere");
    rtSphereObject * ball4 = new rtSphereObject(vertex3d(30,-30,1),15);
    ball4->setName("glass");
    ball4->setMaterial(sphereMat4);
    addObject(ball4,"Sphere");
//    rtSphereObject * ball5 = new rtSphereObject(vertex3d(-60,0,1),15);
//    ball5 ->setName("glass");
//    ball5 ->setMaterial(sphereMat5);
//    addObject(ball5 ,"Sphere");



    rtSphereObject * baseBall = new rtSphereObject(vertex3d(0,0,-15),vertex3d(25,25,15));
    baseBall->setName("base");
    baseBall->setMaterial(snowMat);
    addObject(baseBall,"Sphere");
    rtSphereObject * baseBall2 = new rtSphereObject(vertex3d(0,0,-14),vertex3d(27,27,10));
    baseBall2->setName("base2");
    baseBall2->setMaterial(baseMat);
    addObject(baseBall2,"Sphere");


//    for (int i=0; i < 2; i++)
//    {
//        float nx,ny,nz;
//        nx = 10  - ((qrand()*qrand())%200)/10.0;
//        ny = 10  - ((qrand()*qrand())%200)/10.0;
//        nz = 0   + ((qrand()*qrand())%200)/10.0;
//        rtLight * l  = (new rtLight(colorWhite,vertex3d(nx,ny,nz),0.15f));
//        l->setName("Light");
//        addLight(l);
//    }

    rtLight * l1  = (new rtLight(colorWhite,vertex3d(4,3,1)*20,0.25f));
    l1->setName("Light1");
    addLight(l1);
    rtLight * l2  = (new rtLight(colorWhite,vertex3d(-4,3,1)*20,0.25f));
    l2->setName("Light2");
    addLight(l2);
    rtLight * l3  = (new rtLight(colorWhite,vertex3d(0,-5,1)*20,0.25f));
    l3->setName("Light3");
    addLight(l3);


    addObject(plane1, "plane");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_renderButton_clicked()
{
    rtWindow->setPreview(!rtWindow->preview);
}

void MainWindow::on_addObjectButton_clicked()
{
	objectDialog dialog(this);

	if (dialog.exec() == QDialog::Accepted){
		rtObject *newObject = dialog.getObject();
		QString kind = dialog.getKind();

        addObject(newObject, kind);
    }

}

void MainWindow::on_addTextureButton_clicked()
{
    textureDialog dialog(this);

    if (dialog.exec() == QDialog::Accepted){
        rtTexture *newTexture = dialog.getTexture();
        QString kind = dialog.getKind();

        addTexture(newTexture, kind);
    }
}

void MainWindow::on_editTextureButton_clicked()
{
    int index = ui->textturesList->currentRow();

    if (index < 0) return;

    rtTexture *currentTexture = textures[index];
    textureDialog dialog(this);
    dialog.setTexture(currentTexture);

    if (dialog.exec() == QDialog::Accepted){
        dialog.getTexture();
        ui->textturesList->currentItem()->setText(currentTexture->getName() + " (" + dialog.getKind() + ")");
    }
}

void MainWindow::on_MainWindow_destroyed()
{
    rtWindow->close();
}

void MainWindow::fillTextureCombo(QComboBox *box, rtTexture *exclude)
{
    box->clear();

    // Fill combo with texture list
    for (int i = 0; i < textures.count(); i++){
        rtTexture *tex = textures.at(i);
        box->addItem(tex->getName());
    }
}

void MainWindow::fillMaterialCombo(QComboBox *box)
{
    box->clear();

    // Fill combo with material list
    for (int i = 0; i < materials.count(); i++){
        rtMaterial *mat = materials.at(i);
        box->addItem(mat->getName());
    }
}

void MainWindow::on_addMaterialButton_clicked()
{
    materialDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted){
        rtMaterial *newMaterial = dialog.getMaterial();
        addMaterial(newMaterial);
    }
}

void MainWindow::on_editMaterialButton_clicked()
{
    int index = ui->materialsList->currentRow();
    if (index < 0) return;

    rtMaterial *currentMaterial = materials[index];
    materialDialog dialog(this);
    dialog.setMaterial(currentMaterial);

    if (dialog.exec() == QDialog::Accepted){
        currentMaterial = dialog.getMaterial();
        ui->materialsList->currentItem()->setText(currentMaterial->getName());
    }

}

void MainWindow::on_addLightButton_clicked()
{
    lightDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted){
        rtLight *newLight = dialog.getLight();
        addLight(newLight);
    }
}

void MainWindow::on_editLightButton_clicked()
{
    int index = ui->lightsList->currentRow();
    if (index < 0) return;

    rtLight *currentLight = lights[index];
    lightDialog dialog(this);
    dialog.setLight(currentLight);

	if (dialog.exec() == QDialog::Accepted){
		currentLight = dialog.getLight();
		ui->lightsList->currentItem()->setText(currentLight->getName());
	}

}

void MainWindow::on_editObjectButton_clicked()
{
    int index = ui->objectList->currentRow();
    if (index < 0) return;

    rtObject *currentObject = objects[index];
    objectDialog dialog(this);
    dialog.setObject(currentObject);

	if (dialog.exec() == QDialog::Accepted){
		currentObject = dialog.getObject();
		QString kind = dialog.getKind();

        ui->objectList->currentItem()->setText(currentObject->getName() + " (" + kind + ")");
    }
}

void MainWindow::addTexture(rtTexture *newTexture, QString kind)
{
    textures.append(newTexture);
    ui->textturesList->addItem(newTexture->getName() + " (" + kind + ")");
}

void MainWindow::addMaterial(rtMaterial *newMaterial)
{
    materials.append(newMaterial);
    ui->materialsList->addItem(newMaterial->getName());
}

void MainWindow::addLight(rtLight *newLight)
{
    lights.append(newLight);
    ui->lightsList->addItem(newLight->getName());
}

void MainWindow::addObject(rtObject *newObject, QString kind)
{
    objects.append(newObject);
    ui->objectList->addItem(newObject->getName() + " (" + kind + ")");
}


void MainWindow::setRTWindow(RaytraceWindow *newWindow)
{
    rtWindow = newWindow;
    applySettings();
}

void MainWindow::applySettings()
{
    rtWindow->scene.loadLightList(lights);
    rtWindow->scene.loadObjectList(objects);

    rtWindow->preview = true;
    if (rtWindow->isVisible())
        rtWindow->update();
    else
        rtWindow->show();
}

void MainWindow::on_applyButton_clicked()
{
    applySettings();
}

void MainWindow::on_removeTextureButton_clicked()
{
    int index = ui->textturesList->currentRow();
    if (index < 0) return;

    if (index == 0){
        QMessageBox::warning(this, "Texture", "Cannot remove pre-defined texture (black). Sorry.",
                             QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }

    rtTexture *texture = textures[index];
    deleteTextureRef(texture, voidTexture);

    textures.remove(index);
    QListWidgetItem *temp = ui->textturesList->takeItem(index);

    delete temp;
    delete texture;
}

void MainWindow::deleteTextureRef(rtTexture *texture, rtTexture *voidTexture)
{

    for (int i = 0; i < materials.count(); i++){
        rtMaterial *mat = materials[i];
        if (mat->getAmbientTexture() == texture) mat->setAmbientTexture(voidTexture);
        if (mat->getDiffuseTexture() == texture) mat->setDiffuseTexture(voidTexture);
        if (mat->getSpecularTexture() == texture) mat->setSpecularTexture(voidTexture);
        if (mat->getReflectionTexture() == texture) mat->setReflectionTexture(voidTexture);
        if (mat->getRefractionTexture() == texture) mat->setSpecularTexture(voidTexture);
    }

    for (int i = 0; i < textures.count(); i++){
        rtMaskTexture *maskTexture = dynamic_cast<rtMaskTexture *>(textures[i]);

        if (maskTexture != NULL){
            if (maskTexture->getBlackTexture() == texture) maskTexture->setBlackTexture(voidTexture);
            if (maskTexture->getWhiteTexture() == texture) maskTexture->setWhiteTexture(voidTexture);
            if (maskTexture->getMaskTexture() == texture) maskTexture->setMaskTexture(voidTexture);
        }
    }

}

void MainWindow::deleteMaterialRef(rtMaterial *material, rtMaterial *voidMaterial)
{
    for (int i = 0; i < objects.count(); i++){
        rtObject *object = objects[i];
        if (object->material() == material) object->setMaterial(voidMaterial);
    }
}

void MainWindow::on_removeMaterialButton_clicked()
{
    int index = ui->materialsList->currentRow();
    if (index < 0) return;

    if (ui->materialsList->count() < 2){
        QMessageBox::warning(this, "Material", "Must present at least one material definition!",
                             QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }

    rtMaterial *material = materials[index];
    deleteMaterialRef(material, materials[0]);

    materials.remove(index);
    QListWidgetItem *temp = ui->materialsList->takeItem(index);

    delete temp;
    delete material;
}

void MainWindow::on_removeLightButton_clicked()
{
    int index = ui->lightsList->currentRow();
    if (index < 0) return;

    if (ui->lightsList->count() < 2){
        QMessageBox::warning(this, "Light", "Must present at least one light definition!",
                             QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }

    rtLight *light = lights[index];
    lights.remove(index);
    QListWidgetItem *temp = ui->lightsList->takeItem(index);

    delete temp;
    delete light;
}

void MainWindow::on_removeObjectButton_clicked()
{
    int index = ui->objectList->currentRow();
    if (index < 0) return;

    if (ui->objectList->count() < 2){
        QMessageBox::warning(this, "Object", "Must present at least one object definition!",
                             QMessageBox::Ok, QMessageBox::NoButton);
        return;
    }

    rtObject *object = objects[index];
    objects.remove(index);
    QListWidgetItem *temp = ui->objectList->takeItem(index);

    delete temp;
    delete object;
}

void MainWindow::on_objectList_itemDoubleClicked(QListWidgetItem* )
{
    on_editObjectButton_clicked();
}

void MainWindow::on_materialsList_itemDoubleClicked(QListWidgetItem* )
{
    on_editMaterialButton_clicked();
}

void MainWindow::on_lightsList_itemDoubleClicked(QListWidgetItem* )
{
    on_editLightButton_clicked();
}

void MainWindow::on_textturesList_itemDoubleClicked(QListWidgetItem* )
{
    on_editTextureButton_clicked();
}

void MainWindow::on_copyObjectButton_clicked()
{
    objectDialog dialog(this);

    int index = ui->objectList->currentRow();
    if (index >= 0){
    rtObject *currentObject = objects[index];
    dialog.fillFromObject(currentObject);
    }

	if (dialog.exec() == QDialog::Accepted){
	rtObject *newObject = dialog.getObject();
	QString kind = dialog.getKind();

    addObject(newObject, kind);
    }
}

void MainWindow::on_copyTextureButton_clicked()
{
    textureDialog dialog(this);

    int index = ui->textturesList->currentRow();
    if (index >= 0){
    rtTexture *currentTexture = textures[index];
    dialog.fillFromTexture(currentTexture);
    }

	if (dialog.exec() == QDialog::Accepted){
	rtTexture *newTexture = dialog.getTexture();
	QString kind = dialog.getKind();

    addTexture(newTexture, kind);
    }
}

void MainWindow::on_copyLightButton_clicked()
{
    lightDialog dialog(this);

    int index = ui->lightsList->currentRow();
    if (index >= 0){
    rtLight *currentLight = lights[index];
    dialog.fillFromLight(currentLight);
    }

	if (dialog.exec() == QDialog::Accepted){
	rtLight *newLight = dialog.getLight();

    addLight(newLight);
    }

}

void MainWindow::on_copyMaterialButton_clicked()
{
    materialDialog dialog(this);

    int index = ui->materialsList->currentRow();
    if (index >= 0){
    rtMaterial *currentMaterial = materials[index];
    dialog.fillFromMaterial(currentMaterial);
    }

	if (dialog.exec() == QDialog::Accepted){
	rtMaterial *newMaterial = dialog.getMaterial();

    addMaterial(newMaterial);
    }
}

void MainWindow::on_saveButton_clicked()
{
    QString fileName = QFileDialog::getSaveFileName(this, "Select file", "", "XML files (*.xml)");
    if (fileName != ""){
    rtWindow->scene.save(fileName);
    }
}

void MainWindow::on_loadButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName(this, "Select file", "", "XML files (*.xml)");
    if (fileName != ""){
    rtWindow->scene.load(fileName);
    }
}
