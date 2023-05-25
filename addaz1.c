#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>
#include <lcd.h>

const char PCF8591 = 0x48;
int fd, adcVal;
float vrednost;

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int main()
{
	int lcd;
	
	if (wiringPiSetup() == -1)
		exit (1);
	
	fd = wiringPiI2CSetup(PCF8591);
	
	lcd = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
	
	while(1)
	{
		// procitaj trimer pot sa AIN3 ulaza
		wiringPiI2CReadReg8(fd, PCF8591 + 3);
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 3);
		vrednost = (float)adcVal/255.0 * 3.3;
		printf("%d\n", adcVal);
		
		lcdPosition(lcd, 0, 0);
		lcdPrintf(lcd, "%.2fV ", vrednost);
		
		delay(500);
	}
	
	return 0;
}