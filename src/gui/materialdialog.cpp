#include "materialdialog.h"
#include "ui_materialdialog.h"

materialDialog::materialDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::materialDialog)
{
    ui->setupUi(this);
    mw = (MainWindow *)parent;
    material = NULL;
    fillTextureCombos();

    ui->nameBox->setFocus();
}

materialDialog::~materialDialog()
{
    delete ui;
}

void materialDialog::fillTextureCombos()
{
    mw->fillTextureCombo(ui->ambientTextureBox);
    mw->fillTextureCombo(ui->specularTextureBox);
    mw->fillTextureCombo(ui->diffuseTextureBox);
    mw->fillTextureCombo(ui->reflectionTextureBox);
    mw->fillTextureCombo(ui->refractionTextureBox);
    mw->fillTextureCombo(ui->bumpTextureBox);
}

rtMaterial *materialDialog::getMaterial()
{
    rtMaterial *result = material == NULL ? new rtMaterial() : material;

    result->setName(ui->nameBox->text());
    result->setAmbientTexture(mw->textures[ui->ambientTextureBox->currentIndex()]);
    result->setDiffuseTexture(mw->textures[ui->diffuseTextureBox->currentIndex()]);
    result->setSpecularTexture(mw->textures[ui->specularTextureBox->currentIndex()]);
    result->setReflectionTexture(mw->textures[ui->reflectionTextureBox->currentIndex()]);
    result->setRefractionTexture(mw->textures[ui->refractionTextureBox->currentIndex()]);

    result->setIor(ui->IoRBox->value());
    result->setShiness(ui->shinessBox->value());
    result->setTrans(ui->transBox->value());

    if (ui->bumpBox->isChecked()){
        result->setBump(ui->bumpValueBox->value(), mw->textures[ui->bumpTextureBox->currentIndex()]);
    }
    else
        result->unsetBump();

    return result;
}

void materialDialog::setMaterial(rtMaterial *newMaterial)
{
    material = newMaterial;
    fillFromMaterial(material);
}

void materialDialog::fillFromMaterial(rtMaterial *material)
{
    ui->nameBox->setText(material->getName());

    ui->ambientTextureBox->setCurrentIndex(mw->textures.indexOf(material->getAmbientTexture()));
    ui->diffuseTextureBox->setCurrentIndex(mw->textures.indexOf(material->getDiffuseTexture()));
    ui->specularTextureBox->setCurrentIndex(mw->textures.indexOf(material->getSpecularTexture()));
    ui->reflectionTextureBox->setCurrentIndex(mw->textures.indexOf(material->getReflectionTexture()));
    ui->refractionTextureBox->setCurrentIndex(mw->textures.indexOf(material->getRefractionTexture()));

    ui->bumpBox->setChecked(material->useBump());
    ui->bumpTextureBox->setCurrentIndex(mw->textures.indexOf(material->getBumpMap()));
    ui->bumpValueBox->setValue(material->bumpValue());

    ui->IoRBox->setValue(material->ior());
    ui->shinessBox->setValue(material->shiness());
    ui->transBox->setValue(material->getTrans());
}
