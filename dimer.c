#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

int main() 
{
	int i = 0;
	int taster_old = 0, taster_new = 0;

	if (wiringPiSetup() == -1)
		exit(1);

	pinMode(21, INPUT);
	pinMode(22, INPUT);
	//pinMode(25, OUTPUT);

	//digitalWrite(25, HIGH);

	if(softPwmCreate(28, 0, 100) != 0)
		exit(2);

	i = 0;

	while(1)
	{
		if(!digitalRead(22))
			taster_new = 22;
		else if(!digitalRead(21))
			taster_new = 21;
		else 
			taster_new = 0;
		
		//r_value = digitalRead(21);
		//digitalWrite(25, r_value);

		if (taster_new != taster_old && taster_new != 0)
		{
			if (taster_new == 21)
			{
				if (i <= 80)
					i += 20;
			}
			
			else if (taster_new == 22)
			{
				if (i >= 20)
					i -= 20;
			}

			//printf("i = %d\n", i);
			fflush(stdout);
			
			softPwmWrite(28, i);
			printf("i = %d   |  taster = %d\n", i, taster_new);
			delay(250);
		}

		taster_old = taster_new;	
	}
}