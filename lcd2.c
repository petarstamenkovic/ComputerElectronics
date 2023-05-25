#include <signal.h>
#include <stdlib.h>
#include <stdio.h>
#include <wiringPi.h>
#include <lcd.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

char level0[8] = {0b00000, 0b00000, 0b00000, 0b00000,
				  0b00000, 0b00000, 0b00000, 0b11111};
char level1[8] = {0b00000, 0b00000, 0b00000, 0b00000,
				  0b00000, 0b00000, 0b11111, 0b00000};
char level2[8] = {0b00000, 0b00000, 0b00000, 0b00000,
				  0b00000, 0b11111, 0b00000, 0b00000};
char level3[8] = {0b00000, 0b00000, 0b00000, 0b00000,
				  0b11111, 0b00000, 0b00000, 0b00000};
char level4[8] = {0b00000, 0b00000, 0b00000, 0b11111,
				  0b00000, 0b00000, 0b00000, 0b00000};
char level5[8] = {0b00000, 0b00000, 0b11111, 0b00000,
				  0b00000, 0b00000, 0b00000, 0b00000};
char level6[8] = {0b00000, 0b11111, 0b00000, 0b00000,
				  0b00000, 0b00000, 0b00000, 0b00000};
char level7[8] = {0b11111, 0b00000, 0b00000, 0b00000,
				  0b00000, 0b00000, 0b00000, 0b00000};

#define COLUMNS 16
#define LCD_RS 3
#define LCD_E 14
#define LCD_D4 4
#define LCD_D5 12
#define LCD_D6 13
#define LCD_D7 6

void memory(void);
void volume(void);
void scrollText(void);

char message[] = "Pozdravče!";
int count = 0;
int j = 0;
FILE *mem_file;
char *temp;
int lcd;

int main()
{
	wiringPiSetup();
	
	if(lcd = lcdInit(2, 16, 4, LCD_RS, LCD_E, LCD_D4,
					 LCD_D5, LCD_D6, LCD_D7, 0, 0, 0, 0))
	{
		printf("lcdInit nije uspeo!\n");
		return -1;
	}
	
	int uptimeTimer;
	
	while(1)
	{
		lcdClear(lcd);
		volume();
		sleep(1);
		memory();
		sleep(4);
		lcdClear(lcd);
		sleep(1);
		scrollText();
	}
}

void memory(void)
{
	char MemTotal[35];
	char MemFree[35];
	char total[35];
	char free[35];
	
	lcdClear(lcd);
	
	mem_file=fopen("/proc/meminfo", "r");
	
	if (NULL != mem_file)
	{
		fscanf(mem_file, "%*s%s%*s", MemTotal);
		fscanf(mem_file, "%*s%s%*s", MemFree);
		printf("\x1B[2J"); // brisanje ekrana
		lcdPosition(lcd, 0, 0);
		lcdPrintf(lcd, "MemTotal-%sk", MemTotal);
		lcdPosition(lcd, 0, 1);
		lcdPrintf(lcd, "MemFree - %sk", MemFree);
		fclose(mem_file);
	}
	else
	{
		printf("Otvaranje fajla \"/proc/meminfo\" nije uspelo!\n");
	}
}

void volume(void)
{
	// Definicija specijalnih karaktera za Volume
	lcdCharDef(lcd, 0, level0);
	lcdCharDef(lcd, 1, level1);
	lcdCharDef(lcd, 2, level2);
	lcdCharDef(lcd, 3, level3);
	lcdCharDef(lcd, 4, level4);
	lcdCharDef(lcd, 5, level5);
	lcdCharDef(lcd, 6, level6);
	lcdCharDef(lcd, 7, level7);
	
	lcdClear(lcd);
	
	int i;
	lcdPosition(lcd, 9, 1);
	lcdPuts(lcd, ":Volume");
	for (i = 0; i < 8; i++)
	{
		lcdPosition(lcd, i, 1);
		lcdPutchar(lcd, i);
		usleep(400000);
	}
}

void scrollText(void)
{
	int i, n;
	int h;
	int tempSpace = 0;
	char scrollPadding[] = " ";
	int messageLength = strlen(scrollPadding) + strlen(message);
	for (n = 0; n < messageLength; n++)
	{
		h = COLUMNS;
		usleep(300000);
		printf("\x1B[2J"); // brisanje ekrana
		if (j > messageLength) j = 0;
		for (i = 0; i < j; i++)
		{
			scrollPadding[h-j] = message[i];
			h++;
		}
		
		lcdPosition(lcd, 0, 0);
		lcdClear(lcd);
		lcdPrintf(lcd, "%s", scrollPadding);
		j++;
	}
}