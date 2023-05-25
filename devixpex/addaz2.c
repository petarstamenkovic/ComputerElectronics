#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

const char PCF8591 = 0x48;
int fd, vrednost = 0;
int gore_dole = 1;

int main()
{
	if (wiringPiSetup() == -1)
		exit (1);
	
	fd = wiringPiI2CSetup(PCF8591);
	
	while(1)
	{
		// upisati vrednost u DAC reg, 0x04
		wiringPiI2CWriteReg8(fd, PCF8591 + 4, vrednost);
		
		if (gore_dole)
		{
			vrednost += 5;
			
			if (vrednost == 230)
				gore_dole = 0;
		}
		else
		{
			vrednost -= 5;
			
			if (vrednost == 0)
				gore_dole = 1;
		}
		
		// procitaj DAC preko AIN2
		//wiringPiI2CReadReg8(fd, PCF8591 + 2);
		//adcVal = wiringPiI2CReadReg8(fd, PCF8591 + 2);
		//printf("DAC vrednost = %d \n\n", adcVal);
		
		delay(10);
	}
	
	return 0;
}