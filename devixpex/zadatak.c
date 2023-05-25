#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

int main() 
{
	int i=0, taster0_pritisnut = 0, taster1_pritisnut = 0;
	int r_value0, r_value1;

	if(wiringPiSetup() == -1)
		exit(1);

	pinMode(21, INPUT);
	pinMode(22, INPUT);
	pinMode(25, OUTPUT);
	pinMode(26, OUTPUT);

	digitalWrite(25, HIGH);
	digitalWrite(26, HIGH);
	if(softPwmCreate(28,0,100) != 0)
		exit(2);

	i = 0;

	while(1)
	{
		r_value0 = digitalRead(21);
		r_value1 = digitalRead(22);

		digitalWrite(25, r_value0);
		digitalWrite(26, r_value1);

		if (!r_value0 && !taster0_pritisnut)
		{
			taster0_pritisnut = 1;
			i += 20;
			if (i > 100) i = 100;
		
			printf("i = %d\n", i);
			fflush(stdout);
			softPwmWrite(28, i);	
			delay(200);	
		}
		if (r_value0) taster0_pritisnut = 0;


		if (!r_value1 && !taster1_pritisnut)
		{
			taster1_pritisnut = 1;
			i -= 20;
			if (i < 0) i = 0;
		
			printf("i = %d\n", i);
			fflush(stdout);
			softPwmWrite(28, i);	
			delay(200);	
		}
		if (r_value1) taster1_pritisnut = 0;
	}
	return 0;
}