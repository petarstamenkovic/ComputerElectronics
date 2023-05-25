#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>
#include <unistd.h>

char slovo_d[8] = {0b00000, 
		    0b00000, 
	            0b00000,
                  0b01110,
		    0b01010, 
                  0b01010, 
                 0b11111, 
                   0b10001};

char slovo_zh[8] = {0b00000, 
		   0b00000, 
	          0b00000,
                   0b10001,
		   0b10101, 
                   0b01110, 
                0b10101, 
                   0b10001};

char slovo_dj[8] = {0b01000, 
		    0b11110, 
	            0b01000,
                    0b01111,
		    0b01011, 
                    0b01001, 
                    0b00001, 
                    0b00011};



#define LCD_RS 3
#define LCD_E 14
#define LCD_D4 4
#define LCD_D5 12
#define LCD_D6 13
#define LCD_D7 6

int lcd;
void ispis(void);


int main()
{
	wiringPiSetup();

	if(lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0))
	{
		printf("lcdInit nije uspeo!\n");
		return -1;
	}
	
	lcdClear(lcd);
	ispis();
	while(1);
}

void ispis(void)
{
	// Definicija specijalnih karaktera za Volume
	lcdCharDef(lcd, 0, slovo_d);
	lcdCharDef(lcd, 1, slovo_dj);
	lcdCharDef(lcd, 2, slovo_zh);
	
	lcdClear(lcd);
	lcdPosition(lcd, 0, 0);
	lcdPuts(lcd, "Bo");
	lcdPutchar(lcd, 2);
	lcdPutchar(lcd, 0);
	lcdPosition(lcd, 0, 1);
	lcdPuts(lcd, "Kapa");
	lcdPutchar(lcd, 1);
	lcdPuts(lcd, "op");
	lcdPutchar(lcd, 1);
	lcdPuts(lcd, "e");
	
}
