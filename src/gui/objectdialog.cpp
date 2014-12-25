#include "objectdialog.h"
#include "ui_objectdialog.h"

objectDialog::objectDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::objectDialog)
{
    object = NULL;
    ui->setupUi(this);
    mw = (MainWindow *)parent;

    mw->fillMaterialCombo(ui->materialBox);
    ui->nameBox->setFocus();

    ui->cylinderGroupBox->setVisible(false);
    ui->coneGroupBox->setVisible(false);
}

objectDialog::~objectDialog()
{
    delete ui;
}

void objectDialog::fillFromObject(rtObject *object)
{
    int kindIndex = 0;

    rtPlaneObject *plane = dynamic_cast<rtPlaneObject *>(object);
    rtSphereObject *sphere = dynamic_cast<rtSphereObject *>(object);
    rtConeObject *cone = dynamic_cast<rtConeObject *> (object);
    rtCylinderObject *cyl = dynamic_cast<rtCylinderObject *>(object);
    rtQuadObject *quad = dynamic_cast<rtQuadObject *>(object);
    rtDiskObject *disk = dynamic_cast<rtDiskObject *>(object);

	if(sphere != NULL){
	kindIndex = 1;
	}
	else if(cone != NULL){
	kindIndex = 2;

	ui->coneLowerHeightBox->setValue(cone->getLowerHeight());
	ui->coneUpperHeightBox->setValue(cone->getUpperHeight());
	}
	else if(cyl != NULL){
	kindIndex = 3;
	ui->cylHeightBox->setValue(cyl->getHeight());
	}
	else if(quad != NULL){
	kindIndex = 4;
	}
	else if(disk != NULL){
	kindIndex = 5;
	}
	else if (plane != NULL){
	kindIndex = 0;
	}

    vertex3d pos = object->getPosition();
    ui->posXBox->setValue(pos.x());
    ui->posYBox->setValue(pos.y());
    ui->posZBox->setValue(pos.z());

    vertex3d rot = object->getRotation();
    ui->rotXBox->setValue(rot.x());
    ui->rotYBox->setValue(rot.y());
    ui->rotZBox->setValue(rot.z());

    vertex3d size = object->getSize();
    ui->sizeXBox->setValue(size.x());
    ui->sizeYBox->setValue(size.y());
    ui->sizeZBox->setValue(size.z());
    ui->singleSizeBox->setChecked(size.x() == size.y() && size.y() == size.z());

    ui->nameBox->setText(object->getName());
    ui->materialBox->setCurrentIndex(mw->materials.indexOf(object->material()));

    ui->textureMappingBox->setCurrentIndex(object->getMappingMode());

    ui->kindBox->setCurrentIndex(kindIndex);
    on_kindBox_currentIndexChanged(kindIndex);
}

void objectDialog::setObject(rtObject *newObject)
{

    object = newObject;
    fillFromObject(newObject);
    ui->kindBox->setEnabled(false);
}

rtObject *objectDialog::getObject()
{
    rtObject *result = NULL;

    vertex3d pos(ui->posXBox->value(), ui->posYBox->value(), ui->posZBox->value());
    vertex3d rot(ui->rotXBox->value(), ui->rotYBox->value(), ui->rotZBox->value());
    vertex3d newSize(ui->sizeXBox->value(), ui->sizeYBox->value(), ui->sizeZBox->value());

    int kindIndex = ui->kindBox->currentIndex();
    switch (kindIndex){
    case 0: {
        rtPlaneObject *plane = object == NULL ?
                       new rtPlaneObject() :
                       dynamic_cast<rtPlaneObject *>(object);
        result = (rtObject *)plane;
        break;
    }
    case 1: {
        rtSphereObject *sphere = object == NULL ?
                       new rtSphereObject() :
                       dynamic_cast<rtSphereObject *>(object);

        result = (rtObject *)sphere;
        break;
    }
    case 2: {
        rtConeObject *cone = object == NULL ?
                       new rtConeObject() :
                       dynamic_cast<rtConeObject *>(object);
    cone->setLowerHeight(ui->coneLowerHeightBox->value());
    cone->setUpperHeight(ui->coneUpperHeightBox->value());
        result = (rtObject *)cone;
        break;
    }
    case 3: {
    rtCylinderObject *cyl = object == NULL ?
                new rtCylinderObject :
                dynamic_cast<rtCylinderObject *>(object);
    cyl->setHeight(ui->cylHeightBox->value());
    result = cyl;
    break;
    }

	case 4: {
	rtQuadObject *quad = object == NULL ?
				 new rtQuadObject :
				 dynamic_cast<rtQuadObject *>(object);
	result = quad;
	break;
	}
	case 5: {
	rtDiskObject *disk = object == NULL ?
				 new rtDiskObject :
				 dynamic_cast<rtDiskObject *>(object);
	result = disk;
	break;
	}
	default: break;
	}

	result->setSize(newSize);

    result->setName(ui->nameBox->text());
    result->setPosition(pos);
    result->setRotation(rot);
    result->setMaterial(mw->materials.at(ui->materialBox->currentIndex()));

    result->setMappingMode((rtTextureMappingMode)ui->textureMappingBox->currentIndex());

    return result;
}

void objectDialog::on_kindBox_currentIndexChanged(int index)
{
    ui->coneGroupBox->setVisible(false);
    ui->cylinderGroupBox->setVisible(false);

    switch (ui->kindBox->currentIndex()){
    case 0:{ // plane
    break;
    }
    case 1:{ // sphere
    break;
    }
    case 2:{ // cone
    ui->coneGroupBox->setVisible(true);
    break;
    }
    case 3:{ // cylinder
    ui->cylinderGroupBox->setVisible(true);
    break;
    }
    case 4:{ // quad
    break;
    }
    case 5:{ // disk
    break;
    }
    }
}

QString objectDialog::getKind()
{
    return ui->kindBox->currentText();
}

void objectDialog::on_sizeXBox_valueChanged(double )
{
	if (ui->singleSizeBox->isChecked()){
	ui->sizeYBox->setValue(ui->sizeXBox->value());
	ui->sizeZBox->setValue(ui->sizeXBox->value());
	}
}

void objectDialog::on_sizeYBox_valueChanged(double )
{
	if (ui->singleSizeBox->isChecked()){
	ui->sizeXBox->setValue(ui->sizeYBox->value());
	ui->sizeZBox->setValue(ui->sizeYBox->value());
	}
}

void objectDialog::on_sizeZBox_valueChanged(double )
{
	if (ui->singleSizeBox->isChecked()){
	ui->sizeXBox->setValue(ui->sizeZBox->value());
	ui->sizeYBox->setValue(ui->sizeZBox->value());
	}
}
