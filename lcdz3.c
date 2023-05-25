#include <wiringPi.h>
#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>
#include <unistd.h>

#define LCD_RS 3
#define LCD_E 14
#define LCD_D4 4
#define LCD_D5 12
#define LCD_D6 13
#define LCD_D7 6


int main() 
{
	int taster0_pritisnut = 0, taster1_pritisnut = 0, taster2_pritisnut = 0, taster3_pritisnut = 0;
	int lcd;
	int r_value0, r_value1, r_value2, r_value3;
	int x = 0;
	int y = 0;

	if (wiringPiSetup() == -1)
		exit(1);

	if(lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0))
	{
		printf("lcdInit nije uspeo!\n");
		return -1;
	}

	pinMode(21, INPUT);
	pinMode(22, INPUT);
	pinMode(23, INPUT);
	pinMode(24, INPUT);
	
	lcdClear(lcd);
	lcdCursor(lcd, 1);

	while(1)
	{
		r_value0 = digitalRead(21);
		r_value1 = digitalRead(22);
		r_value2 = digitalRead(23);
		r_value3 = digitalRead(24);

		if (!r_value0 && !taster0_pritisnut)
		{
			taster0_pritisnut = 1;
			x++;
			if (x > 15) x = 0;
			delay(200);	
		}
		if (r_value0) taster0_pritisnut = 0;


		if (!r_value1 && !taster1_pritisnut)
		{
			taster1_pritisnut = 1;
			x--;
			if (x < 0) x = 15;
			delay(200);	
		}
		if (r_value1) taster1_pritisnut = 0;

		if (!r_value2 && !taster2_pritisnut)
		{
			taster2_pritisnut = 1;
			y++;
			if (y > 1) y = 0;
			delay(200);	
		}
		if (r_value2) taster2_pritisnut = 0;

		if (!r_value3 && !taster3_pritisnut)
		{
			taster3_pritisnut = 1;
			y--;
			if (y < 0) y = 1;
			delay(200);	
		}
		if (r_value3) taster3_pritisnut = 0;

		lcdPosition(lcd, x, y);
	
	}
}