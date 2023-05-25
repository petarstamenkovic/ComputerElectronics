#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

unsigned char b[] = {0x40, 0x00};

int main(void)
{
	if (!bcm2835_init())
		return 1;
	
	bcm2835_i2c_begin();
	bcm2835_i2c_setSlaveAddress(0x48);
	bcm2835_i2c_set_baudrate(10000);
	
	while(1)
	{
		b[1] = b[1] + 5;
		bcm2835_i2c_write((const char *) &b, 2);
		printf("Izlaz DA konvertora: %d \n", b[1]);
		bcm2835_delay(50);
	}
	
	bcm2835_i2c_end();
	bcm2835_close();
	return 0;
}  