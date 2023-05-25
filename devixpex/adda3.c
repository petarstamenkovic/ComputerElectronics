#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

const char PCF8591 = 0x48;
int fd, adcVal;

int main()
{
	if (wiringPiSetup() == -1)
		exit (1);
	
	fd = wiringPiI2CSetup(PCF8591);
	
	while(1)
	{
		// procitaj trimer pot sa AIN3 ulaza
		wiringPiI2CReadReg8(fd, PCF8591 + 3);
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 3);
		printf("Pot ADC vrednost = %d", adcVal);
		
		// upisi  tu vrednost u DAC reg, 0x04
		wiringPiI2CWriteReg8(fd, PCF8591 + 4, adcVal);
		
		// procitaj DAC preko AIN2
		wiringPiI2CReadReg8(fd, PCF8591 + 2);
		adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 2);
		printf(" DAC vrednost = %d \n\n", adcVal);
		
		delay(500);
	}
	
	return 0;
}