#include "transformwavefrontdlg.h"
#include "ui_transformwavefrontdlg.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "surfacemanager.h"
TransformWaveFrontDlg::TransformWaveFrontDlg( QWidget *parent, double wavelength) :
    QDialog(parent),
    ui(new Ui::TransformWaveFrontDlg)
{
    ui->setupUi(this);
    ui->newWaveLength->setValue(wavelength);
}

TransformWaveFrontDlg::~TransformWaveFrontDlg()
{
    delete ui;
}



void TransformWaveFrontDlg::on_ChangeWaveLength_clicked()
{
    emit changeWavelength(ui->newWaveLength->value());
}

void TransformWaveFrontDlg::on_flipLR_clicked()
{
    emit flipLR();


}

void TransformWaveFrontDlg::on_Resize_clicked()
{
    emit resizeW( ui->newSize->value());
}

void TransformWaveFrontDlg::on_flipVertical_clicked()
{
    emit flipV();
}
