#include "texturedialog.h"
#include "ui_texturedialog.h"
#include <QFileDialog>
#include "mainwindow.h"

textureDialog::textureDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::textureDialog)
{
    ui->setupUi(this);
    texture = NULL;
    mw = (MainWindow*)parent;

    ui->imageGroupBox->setVisible(false);
    ui->solidColorGroupBox->setVisible(true);
    ui->maskGroupBox->setVisible(false);
    ui->normalMapGroupBox->setVisible(false);

    fill_combos();
    ui->nameBox->setFocus();
}

textureDialog::~textureDialog()
{
    delete ui;
}

rtTexture *textureDialog::getTexture()
{

    rtTexture *result = NULL;

    switch (ui->kindBox->currentIndex())
    {
    case 0:{
        Color3 color(ui->redColorBox->value(), ui->greenColorBox->value(), ui->blueColorBox->value());
        rtSolidColorTexture *rtsc = texture == NULL ?
                                            new rtSolidColorTexture(color) :
                                            dynamic_cast<rtSolidColorTexture *>(texture);
        rtsc->setSolidColor(color);
        result = (rtTexture *)rtsc;
        break;
    }
    case 1:{

        rtMaskTexture *rtmt = texture == NULL ?
                              new rtMaskTexture():
                              dynamic_cast<rtMaskTexture *>(texture);
        rtmt->setBlackTexture(mw->textures.at(ui->blackMaskBox->currentIndex()));
        rtmt->setWhiteTexture(mw->textures.at(ui->whiteMaskBox->currentIndex()));
        rtmt->setMaskTexture(mw->textures.at(ui->textureMaskBox->currentIndex()));

        result = (rtTexture *)rtmt;
        break;
    }
    case 2:{
        rtImageTexture *rtit = texture == NULL ?
                               new rtImageTexture():
                               dynamic_cast<rtImageTexture *>(texture);
        rtit->setFileName(ui->textureFileName->text());
        result = (rtTexture *)rtit;
        break;
    }
    case 3:{
        rtNormalMap *rtnm = texture == NULL ?
                               new rtNormalMap():
                               dynamic_cast<rtNormalMap *>(texture);

        rtnm->setFileName(ui->mapTextureFileName->text());
        rtnm->setMean(ui->meanBox->checkState() == Qt::Checked);
        rtnm->load();

        result = (rtTexture *)rtnm;
        break;
    }
    default: break;
    }

    result->setName(ui->nameBox->text());
    result->setTile(ui->tileUBox->value(), ui->tileVBox->value());

    return result;
}

QString textureDialog::getKind()
{
    return ui->kindBox->currentText();
}

void textureDialog::fillFromTexture(rtTexture *texture)
{
    int kindIndex = 0;

    rtSolidColorTexture *solid = dynamic_cast<rtSolidColorTexture *>(texture);
    rtMaskTexture *mask = dynamic_cast<rtMaskTexture *>(texture);
    rtImageTexture *image = dynamic_cast<rtImageTexture *>(texture);
    rtNormalMap *normap = dynamic_cast<rtNormalMap *>(texture);

    if (solid != NULL){
	kindIndex = 0;
	Color3 solidColor = solid->getSolidColor();

	ui->redColorBox->setValue(solidColor.r);
	ui->greenColorBox->setValue(solidColor.g);
	ui->blueColorBox->setValue(solidColor.b);
    }
    else if (mask != NULL){
	kindIndex = 1;

	ui->blackMaskBox->setCurrentIndex(mw->textures.indexOf(mask->getBlackTexture()));
	ui->whiteMaskBox->setCurrentIndex(mw->textures.indexOf(mask->getWhiteTexture()));
	ui->textureMaskBox->setCurrentIndex(mw->textures.indexOf(mask->getMaskTexture()));
    }
    else if (normap != NULL){
	kindIndex = 3;
	ui->mapTextureFileName->setText(normap->getFileName());
	ui->meanBox->setChecked(normap->getMean());
    }
    else if (image != NULL){
	kindIndex = 2;
	ui->textureFileName->setText(image->getFileName());
    };

    ui->nameBox->setText(texture->getName());

    ui->tileUBox->setValue(texture->getTileU());
    ui->tileVBox->setValue(texture->getTileV());

    ui->kindBox->setCurrentIndex(kindIndex);
    on_kindBox_currentIndexChanged(kindIndex);
}

void textureDialog::setTexture(rtTexture *newTexture)
{
    texture = newTexture;
    fill_combos();

    fillFromTexture(newTexture);

    ui->kindBox->setEditable(false);
    ui->kindBox->setEnabled(false);
}

void textureDialog::on_kindBox_currentIndexChanged(int index)
{

    ui->imageGroupBox->setVisible(false);
    ui->solidColorGroupBox->setVisible(false);
    ui->maskGroupBox->setVisible(false);
    ui->normalMapGroupBox->setVisible(false);

    switch (ui->kindBox->currentIndex())
    {
    case 0:{
        ui->solidColorGroupBox->setVisible(true);
        break;
    }
    case 1:{
        ui->maskGroupBox->setVisible(true);
        break;
    }
    case 2:{
        ui->imageGroupBox->setVisible(true);
        break;
    }
    case 3:{
        ui->normalMapGroupBox->setVisible(true);
        break;
    }
    default: break;
    }
}

void textureDialog::on_redColorBox_valueChanged(int )
{
    QColor color(ui->redColorBox->value(), ui->greenColorBox->value(), ui->blueColorBox->value());
    // TODO: set a color example
}

void textureDialog::on_selectImageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName((QWidget*)this, "select texture", "", "Images (*.jpg *.jpeg *.png *.bmp)");
    if (fileName != ""){
        ui->textureFileName->setText(fileName);
    }
}

void textureDialog::fill_combos()
{
    mw->fillTextureCombo(ui->whiteMaskBox, texture);
    mw->fillTextureCombo(ui->blackMaskBox, texture);
    mw->fillTextureCombo(ui->textureMaskBox, texture);
}

void textureDialog::on_mapSelectImageButton_clicked()
{
    QString fileName = QFileDialog::getOpenFileName((QWidget*)this, "select texture", "", "Images (*.jpg *.jpeg *.png *.bmp)");
    if (fileName != ""){
        ui->mapTextureFileName->setText(fileName);
    }
}
