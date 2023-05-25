// lcd1602.c
// kompajlirati sa -lwiringPi -lwiringPiDev

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <lcd.h>

// dodela vrednosti za konkretne pinove
// prema gornjoj tabeli i semi DVK512
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

int main()
{
	wiringPiSetup();
	int lcd_h;
	
	if(wiringPiSetup < 0)
	{
		fprintf (stderr, "Greska pri inicijalizaciji: %s\n", strerror (errno));
		return 1;
	}
	
	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
	lcdPosition(lcd_h, 0, 0);
	lcdPrintf(lcd_h, "Displej sa 16ch");
	lcdPosition(lcd_h, 0, 1);
	lcdPrintf(lcd_h, "u 2 reda");
	while(1);
	
	lcdClear(lcd_h);
}