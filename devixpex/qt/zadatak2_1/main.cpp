#include "dialog.h"
#include <wiringPi.h>
#include <softPwm.h>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    wiringPiSetup();
    if(softPwmCreate(25, 0, 100) != 0)
        exit(2);
    softPwmWrite(25, 0);
    Dialog w;
    w.show();
    return a.exec();
}
