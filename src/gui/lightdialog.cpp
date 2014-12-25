#include "lightdialog.h"
#include "ui_lightdialog.h"

lightDialog::lightDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lightDialog)
{
    ui->setupUi(this);
    light = NULL;
}

lightDialog::~lightDialog()
{
    delete ui;
}

rtLight *lightDialog::getLight()
{

    rtLight *result = light == NULL ? new rtLight() : light;
    Color3 color (ui->colRBox->value(), ui->colGBox->value(), ui->colBBox->value());
    vertex3d lightPos(ui->posXBox->value(), ui->posYBox->value(), ui->posZBox->value());

    result->setColor(color);
    result->setPosition(lightPos);
    result->setName(ui->nameBox->text());
    result->setIntensity(ui->intensityBox->value());

    return result;
}

void lightDialog::setLight(rtLight *newLight)
{
    light = newLight;
    fillFromLight(light);
}

void lightDialog::fillFromLight(rtLight *light)
{
    Color3 color = light->getColor();
    vertex3d pos = light->getPosition();

    ui->posXBox->setValue(pos.x());
    ui->posYBox->setValue(pos.y());
    ui->posZBox->setValue(pos.z());

    ui->colRBox->setValue(color.r);
    ui->colGBox->setValue(color.g);
    ui->colBBox->setValue(color.b);

    ui->intensityBox->setValue(light->getIntensity());
    ui->nameBox->setText(light->getName());
}
