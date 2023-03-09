#include<stdio.h>
#include<softPwm.h>
#include<wiringPi.h>

#define SVETLIJE 1
#define TAMNIJE 2
void readButton()
{
	int r_value;

	if(digitalRead(21) == LOW)
		return SVETLIJE;
	if(digitalRead(22) == LOW)
		return TAMNIJE;
	return 0;
}

int main(){
	int i = 0, taster_pritisnut = 0;

	if(wiringPiSetup() == -1)
		exit(1);
	
	pinMode(21,INPUT);
	pinMode(22,INPUT);
	pinMode(25,OUTPUT);

	digitalWrite(25,HIGH);

	if(softPwmCreate(28,0,100) != 0)
		exit(2);
	
	i = 0;
	taster_pritisnut = 0;

	while(1)
	{
		taster_pritisnut = readButton();
		if(taster_pritisnut == SVETLIJE)
		{
			i += 20;
			if(i>100)
				i = 100;
			printf("i = %d\n", i);
			fflush(stdout);

			softPwmWrite(28,i);
		}
		if(taster_pritisnut == TAMNIJE){
			i -= 20;
			if ( i < 0 )
				i = 0;
			pritnf("i = %d\n", i);
			fflusth(stdout);

			softPwmWrite(28,i);

		}
		if(taster_pritisnut == 0)
			taster_pritisnut = 0;
	}
}
