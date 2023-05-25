#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

unsigned char WriteBuf;
unsigned char ReadBuf0, ReadBuf1, ReadBuf2, ReadBuf3;

int main(int argc, char **argv)
{
	if (!bcm2835_init())
		return 1;
	
	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(0x48);
	bcm2835_i2c_set_baudrate(10000);
	
	while(1)
	{
		WriteBuf = 0x00;
		bcm2835_i2c_write_read_rs(&WriteBuf, 1, &ReadBuf0, 1);
		bcm2835_i2c_read(&ReadBuf0, 1);
		
		WriteBuf = 0x01;
		bcm2835_i2c_write_read_rs(&WriteBuf, 1, &ReadBuf1, 1);
		bcm2835_i2c_read(&ReadBuf1, 1);
		
		WriteBuf = 0x02;
		bcm2835_i2c_write_read_rs(&WriteBuf, 1, &ReadBuf2, 1);
		bcm2835_i2c_read(&ReadBuf2, 1);
		
		WriteBuf = 0x03;
		bcm2835_i2c_write_read_rs(&WriteBuf, 1, &ReadBuf3, 1);
		bcm2835_i2c_read(&ReadBuf3, 1);
		
		printf("adc0: %5.2f adc1: %5.2f adc2: %5.2f adc3: %5.2f\n",
		(double) ReadBuf0 * 3.3 / 255, (double) ReadBuf1 * 3.3 / 255,
		(double) ReadBuf2 * 3.3 / 255, (double) ReadBuf3 * 3.3 / 255);
		
		printf("\r");
		fflush(stdout);
		
		bcm2835_delay(100);
	}
	
	bcm2835_i2c_end();
	bcm2835_close();
	return 0;
}