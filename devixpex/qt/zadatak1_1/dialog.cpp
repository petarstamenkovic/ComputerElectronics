#include "dialog.h"
#include "ui_dialog.h"
#include <wiringPi.h>

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->label->setPixmap(QPixmap(":/slike/toggle_off.jpg"));
}

Dialog::~Dialog()
{
    delete ui;
}


void Dialog::on_pushButton_clicked(bool checked)
{
    if(checked)
    {
        digitalWrite(25, HIGH);
        ui->label->setPixmap(QPixmap(":/slike/toggle_on.jpg"));
    }
    else
    {
        digitalWrite(25, LOW);
        ui->label->setPixmap(QPixmap(":/slike/toggle_off.jpg"));
    }
}

void Dialog::on_pushButton_2_clicked(bool checked)
{
    if(checked)
        digitalWrite(26, HIGH);
    else
        digitalWrite(26, LOW);
}

void Dialog::on_pushButton_3_clicked(bool checked)
{
    if(checked)
        digitalWrite(27, HIGH);
    else
        digitalWrite(27, LOW);
}

void Dialog::on_pushButton_4_clicked(bool checked)
{
    if(checked)
        digitalWrite(28, HIGH);
    else
        digitalWrite(28, LOW);
}
