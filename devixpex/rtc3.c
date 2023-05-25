// Primer rada sa PCF8563 koji ispisuje tekuce vreme
// u terminalu svakih 5 sekundi
#include <errno.h>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdio.h>
#include <unistd.h>
#include <lcd.h>
#include <string.h>

#define changeHexToInt(hex) ((((hex)>>4)*10)+((hex)%16))

// adrese registara
#define SEK 0x02
#define MINUT 0x03
#define SAT 0x04
#define DAN 0x05
#define RDAN 0x06
#define MES 0x07
#define GDN 0x08

const int RS = 3;
const int EN = 14;
const int D0 = 4;
const int D1 = 12;
const int D2 = 13;
const int D3 = 6;

unsigned char WriteBuf[2];
unsigned char ReadBuf;
unsigned char g8563_Store[7];
			   //     sek    min  sat   dan   rds   msc   gdn
unsigned char init8563_Store[7]={0x15, 0x55, 0x19, 0x30, 0x03, 0x03, 0x23};

void P8563_settime(int fd)
{
	WriteBuf[0] = SEK;
	WriteBuf[1] = g8563_Store[0];
	wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);
	
	WriteBuf[0] = MINUT;
	WriteBuf[1] = g8563_Store[1];
	wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);
	
	WriteBuf[0] = SAT;
	WriteBuf[1] = g8563_Store[2];
	wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);

	WriteBuf[0] = DAN;
	WriteBuf[1] = g8563_Store[3];
	wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);

	WriteBuf[0] = RDAN;
	WriteBuf[1] = g8563_Store[4];
	wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);

	WriteBuf[0] = MES;
	WriteBuf[1] = g8563_Store[5];
	wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);
// WiringPiI2CReg
	WriteBuf[0] = GDN;
	WriteBuf[1] = g8563_Store[6];
	wiringPiI2CWriteReg8(fd, WriteBuf[0], WriteBuf[1]);
}

void P8563_init()
{
	unsigned char i;
	
	for(i = 0; i <= 7; i++)
		g8563_Store[i] = init8563_Store[i];
	
	P8563_settime(3);
	//printf("Postavi pocetno tekuce vreme\n");
	
	//inicijalizacija RTC-a
	WriteBuf[0] = 0x0;
	WriteBuf[1] = 0x00; // normalni rezim rada
	wiringPiI2CWriteReg16(3, WriteBuf[0], WriteBuf[1]);
}

void P8563_Readtime()
{
	unsigned char time[7];
	
	WriteBuf[0] = SEK;
	g8563_Store[0] = wiringPiI2CReadReg8(3, WriteBuf[0]) & 0x7f;

	WriteBuf[0] = MINUT;
	g8563_Store[1] = wiringPiI2CReadReg8(3, WriteBuf[0]) & 0x7f;

	WriteBuf[0] = SAT;
	g8563_Store[2] = wiringPiI2CReadReg8(3, WriteBuf[0]) & 0x3f;

	WriteBuf[0] = DAN;
	g8563_Store[3] = wiringPiI2CReadReg8(3, WriteBuf[0]) & 0x3f;

	WriteBuf[0] = RDAN;
	g8563_Store[4] = wiringPiI2CReadReg8(3, WriteBuf[0]) & 0x07;

	WriteBuf[0] = MES;
	g8563_Store[5] = wiringPiI2CReadReg8(3, WriteBuf[0]) & 0x1f;

	WriteBuf[0] = GDN;
	g8563_Store[6] = wiringPiI2CReadReg8(3, WriteBuf[0]) & 0xff;


	//g8563_Store[0] = time[0] & 0x7f;
	//g8563_Store[1] = time[1] & 0x7f;
	//g8563_Store[2] = time[2] & 0x3f;
	//g8563_Store[3] = time[3] & 0x3f;
	//g8563_Store[4] = time[4] & 0x07;
	//g8563_Store[5] = time[5] & 0x1f;
	//g8563_Store[6] = time[6] & 0xff;
	
	g8563_Store[0] = changeHexToInt(g8563_Store[0]);
	g8563_Store[1] = changeHexToInt(g8563_Store[1]);
	g8563_Store[2] = changeHexToInt(g8563_Store[2]);
	g8563_Store[3] = changeHexToInt(g8563_Store[3]);
	g8563_Store[4] = changeHexToInt(g8563_Store[4]);
	g8563_Store[5] = changeHexToInt(g8563_Store[5]);
	g8563_Store[6] = changeHexToInt(g8563_Store[6]);
}

int main(int argc, char **argv)
{
	
	if(wiringPiSetup < 0)
	{
		fprintf (stderr, "Greska pri inicijalizaciji: %s\n", strerror (errno));
		return 1;
	}
	int lcd;
	int fd = wiringPiI2CSetup(0x51);
	wiringPiSetup();
	if (fd == -1)
		return 1;
	
	printf("start............\n");
	P8563_init();

	lcd = lcdInit(2, 16, 4, RS, EN, D0, D1, D2, D3, D0, D1, D2, D3);
	lcdClear(lcd);

	//int podatak[7];
	

	while(1)
	{
		P8563_Readtime();
		printf("Debug\n");
		printf("Sati:%d | Minuti: %d | Sekunde: %d | Dan: %d | Mesec: %d | Godina: 20%d \n",
		     	g8563_Store[2], g8563_Store[1], g8563_Store[0],
				g8563_Store[3], g8563_Store[5], g8563_Store[6]);

		

		lcdPosition(lcd, 0, 0);
		lcdPrintf(lcd, "%d.%d.20%d.", (int) g8563_Store[3], (int) g8563_Store[5], (int) g8563_Store[6]);
		lcdPosition(lcd, 0, 1);
		lcdPrintf(lcd, "%d.%d.%d.", (int) g8563_Store[2], (int) g8563_Store[1], (int) g8563_Store[0]);
		
		delay(5000);
	}
	
	
	return 0;
}