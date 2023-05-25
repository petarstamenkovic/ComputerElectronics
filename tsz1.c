#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

double temperatura(void) 	//ocitavanje temperature
{
	FILE *ft;
	char tekst[100];
	ft = fopen("/sys/bus/w1/devices/28-000007237df2/w1_slave", "r");
	
	if (ft == NULL) return 0;
	
	int i = 0;
	for (i = 0; i < 22; i++)		//samo temperatura
		fscanf(ft, "%s", tekst);
	
	fclose(ft);
	
	//obrisati "t="
	for(i = 0; i < 10; i++) tekst[i] = tekst[i+2];
	
	int temp = atoi(tekst);
	double tem = (double) temp/1000;
	
	return tem;
}



int main(void)
{
	wiringPiSetup();
	int j = 0;
	double temp;
	pinMode(25, OUTPUT);
	digitalWrite(25, 0);
	
	temp = temperatura();
	printf("\n\nPocetna Temp = %.3f \xC2\xB0 C", temp);
	
	while(1)
	{
		j++;
		temp = temperatura();
		printf("\nMerenje br. %d.\tTemp = %.3f \xC2\xB0 C", j, temp);
		if(temp > 27)
		{
			digitalWrite(25, 1);
			delay(500);
			digitalWrite(25, 0);
			delay(500);
		}
		
	}
}