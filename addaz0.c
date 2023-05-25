#include <bcm2835.h>
#include <stdio.h>
#include <unistd.h>

unsigned char WriteBuf;
unsigned char ReadBuf3;

int main(int argc, char **argv)
{
    if (!bcm2835_init())
        return 1;

    bcm2835_i2c_begin();
    bcm2835_i2c_setSlaveAddress(0x48);
    bcm2835_i2c_set_baudrate(10000);

    while (1) 
	{
		WriteBuf = 0x03;
		bcm2835_i2c_write_read_rs(&WriteBuf, 1, &ReadBuf3, 1);
		bcm2835_i2c_read(&ReadBuf3, 1);
        
        printf("Ocitavanje napona: %5.2f V\n", (double) ReadBuf3 * 3.3 / 255);

        bcm2835_delay(500);
    }

    bcm2835_i2c_end();
    bcm2835_close();
    return 0;
}