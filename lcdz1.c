// lcd1602.c
// kompajlirati sa -lwiringPi -lwiringPiDev

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <wiringPi.h>
#include <lcd.h>
#include <stdlib.h>

// dodela vrednosti za konkretne pinove
// prema gornjoj tabeli i semi DVK512
const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

double temperatura(void) 	//ocitavanje temperature
{
	FILE *ft;
	char tekst[100];
	ft = fopen("/sys/bus/w1/devices/28-00000e72d781/w1_slave", "r");
	
	if (ft == NULL) return 0;
	
	int i = 0;
	for (i = 0; i < 22; i++)		//samo temperatura
		fscanf(ft, "%s", tekst);
	
	fclose(ft);
	
	//obrisati "t="
	for(i = 0; i < 10; i++) tekst[i] = tekst[i+2];
	
	int temp = atoi(tekst);
	double tem = (double) temp/1000;
	
	return tem;
}

int main()
{
	wiringPiSetup();
	int lcd_h;
	double temp;
	double a=5;
	
	if(wiringPiSetup < 0)
	{
		fprintf (stderr, "Greska pri inicijalizaciji: %s\n", strerror (errno));
		return 1;
	
	}
	lcd_h = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
	lcdClear(lcd_h);

	while(1)
	{
		temp = temperatura();
		lcdPosition(lcd_h, 0, 0);
		lcdPrintf(lcd_h, "Temperatura:");
		lcdPosition(lcd_h, 0, 1);
		lcdPrintf(lcd_h, "%.3f", temp);
	}
}