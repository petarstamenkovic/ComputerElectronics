#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>
#include <stdio.h>

int fd, vrednost;

int main()
{
    if (wiringPiSetup() == -1) 
	{
        return 1;
    }
    
    fd = wiringPiI2CSetup(0x48);
	
	pinMode(25, OUTPUT);
	pinMode(26, OUTPUT);
	pinMode(27, OUTPUT);
	
	digitalWrite(25, LOW);
	digitalWrite(26, LOW);
	digitalWrite(27, LOW);
    
    while (1) 
	{
        vrednost = wiringPiI2CReadReg8(fd, 0x48);
	printf("%d  |  ", vrednost);
        
        if (vrednost < 84) 
		{
            digitalWrite(25, HIGH);
			digitalWrite(26, LOW);
			digitalWrite(27, LOW);
			printf("DNEVNO\n");
        } 
		else if (vrednost < 168) 
		{
            digitalWrite(25, LOW);
			digitalWrite(26, HIGH);
			digitalWrite(27, LOW);
			printf("SLABO\n");
        } 
		else 
		{
            digitalWrite(25, LOW);
			digitalWrite(26, LOW);
			digitalWrite(27, HIGH);
			printf("NOCNO\n");
        }
	
        
        delay(500);
    }
    
    return 0;
}
