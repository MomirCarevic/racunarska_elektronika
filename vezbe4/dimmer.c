#include<stdio.h>
#include<softPwm.h>
#include<wiringPi.h>

int main() {
	int i = 0, taster_pritisnut = 0;
	int r_value;

	if (wiringPiSetup() == -1)
		exit(1);
	
	pinMode(21,INPUT);	//taster KEY0
	pinMode(25,OUTPUT);	//ledovka LED3

	digitalWrite(25,HIGH);

	if (softPwmCreate(28,0,100) != 0)
		eixt(2);

	i = 0;
	taster_pritisnut = 0;

	while(1)
	{
		r_value = digitalRead(21); //procitaj KEY0
		digitalWrite(25,r_value);
		
		// softversko diferenciranje, cekamo pritisak tastera

		if(!r_value && !taster_pritisnut)
		{
			taster_pritisnut = 1;
			
			i += 20;
			if(i>100)
				i=0;
			//intezitet se menja za 20%, kada dosegne 100% sledeci pritisak ga vraca na nulu

			printf("i = %d\n", i );
			fflush(stdout);

			softPwmWrite(28,i);
		}
		if(r_value)
				taster_pritisnut = 0;
	}
}
