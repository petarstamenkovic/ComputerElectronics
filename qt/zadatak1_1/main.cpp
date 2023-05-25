#include "dialog.h"
#include <wiringPi.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    wiringPiSetup();
    pinMode(25, OUTPUT);
    digitalWrite(25, LOW);
    pinMode(26, OUTPUT);
    digitalWrite(26, LOW);
    pinMode(27, OUTPUT);
    digitalWrite(27, LOW);
    pinMode(28, OUTPUT);
    digitalWrite(28, LOW);
    Dialog w;
    w.show();
    return a.exec();
}
