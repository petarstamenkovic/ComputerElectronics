// Primer rada sa PCF8563 koji ispisuje tekuce vreme
// u terminalu svakih 5 sekundi

#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

#define changeHexToInt(hex) ((((hex)>>4)*10)+((hex)%16))

// adrese registara
#define SEK 0x02
#define MINUT 0x03
#define SAT 0x04

unsigned char WriteBuf[2];
unsigned char ReadBuf;
unsigned char g8563_Store[3];
							  //  sek   min   sat
unsigned char init8563_Store[3]={0x0, 0x20, 0x18};

void P8563_settime()
{
	WriteBuf[0] = SEK;
	WriteBuf[1] = g8563_Store[0];
	bcm2835_i2c_write(WriteBuf, 2);
	
	WriteBuf[0] = MINUT;
	WriteBuf[1] = g8563_Store[1];
	bcm2835_i2c_write(WriteBuf, 2);
	
	WriteBuf[0] = SAT;
	WriteBuf[1] = g8563_Store[2];
	bcm2835_i2c_write(WriteBuf, 2);
}

void P8563_init()
{
	unsigned char i;
	
	for(i = 0; i <= 3; i++)
		g8563_Store[i] = init8563_Store[i];
	
	P8563_settime();
	printf("Postaavi pocetno tekuce vreme\n");
	
	//inicijalizacija RTC-a
	WriteBuf[0] = 0x0;
	WriteBuf[1] = 0x00; // normalni rezim rada
	bcm2835_i2c_write(WriteBuf, 2);
}

void P8563_Readtime()
{
	unsigned char time[7];
	
	WriteBuf[0] = SEK;
	bcm2835_i2c_write_read_rs(WriteBuf, 1, time, 7);
	
	g8563_Store[0] = time[0] & 0x7f;
	g8563_Store[1] = time[1] & 0x7f;
	g8563_Store[2] = time[2] & 0x7f;
	
	g8563_Store[0] = changeHexToInt(g8563_Store[0]);
	g8563_Store[1] = changeHexToInt(g8563_Store[1]);
	g8563_Store[2] = changeHexToInt(g8563_Store[2]);
}

int main(int argc, char **argv)
{
	if (!bcm2835_init())
		return 1;
	
	bcm2835_i2c_begin();
	
	// adresa PCF8563 na I2C magistrali
	bcm2835_i2c_setSlaveAddress(0x51);
	bcm2835_i2c_set_baudrate(10000);
	printf("start............\n");
	P8563_init();
	
	while(1)
	{
		P8563_Readtime();
		
		printf("Sati:%d | Minuti: %d | Sekunde: %d\n",
				g8563_Store[2], g8563_Store[1], g8563_Store[0]);
		
		bcm2835_delay(5000);
	}
	
	bcm2835_i2c_end();
	bcm2835_close();
	
	return 0;
}