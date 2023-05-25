#include "dialog.h"
#include "ui_dialog.h"
#include <wiringPi.h>
#include <softPwm.h>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_verticalSlider_valueChanged(int value)
{
    softPwmWrite(25, value);
}
