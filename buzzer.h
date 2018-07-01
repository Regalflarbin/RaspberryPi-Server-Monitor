#include <iostream>
#include <chrono>
#include <ctime>
#include <cmath>
#include <wiringPi.h>
#include <stdio.h>

#include <softTone.h> //http://wiringpi.com/reference/software-tone-library/
/*When compiling your program you must include the pthread library as well as the wiringPi library:

cc - o myprog myprog.c - lwiringPi - lpthread
You must initialise wiringPi with one of wiringPiSetup(), wiringPiSetupGpio() or wiringPiSetupPhys() functions.wiringPiSetupSys() is not fast enough, so you must run your programs with sudo.*/


int buzzerPin = 23; //I believe this pin has power modulation as is useful for changing buzzer sound
int delayTime = 1000; //adjust as needed to provide satisfying "racing countdown" delay

class Buzzer
{
public:
	void setupBuzzer()
	{
		pinMode(buzzerPin, OUTPUT);
	}

	void startBasicRacingBuzzer()				//simple method
	{
		digitalWrite(buzzerPin, HIGH);			//on
		delay(delayTime);						//wait while on
		digitalWrite(buzzerPin, LOW);			//off
		delay(delayTime);						//wait while off

		digitalWrite(buzzerPin, HIGH);
		delay(delayTime);
		digitalWrite(buzzerPin, LOW);
		delay(delayTime);

		digitalWrite(buzzerPin, HIGH);
		delay(delayTime);
		digitalWrite(buzzerPin, LOW);
		delay(delayTime);

		digitalWrite(buzzerPin, HIGH);
		delay(delayTime);
		digitalWrite(buzzerPin, LOW);		
	}

	void startRacingBuzzer()					//advanced method
	{
		softToneCreate(buzzerPin);
		for (int i = 0; i < 3; i = i + 1)		//buzz low three times
		{
			softToneWrite(buzzerPin, 500);		//on, low pitch
			delay(delayTime);					//wait
			softToneWrite(buzzerPin, 0);		//off
			delay(delayTime);					//wait
		}

		softToneWrite(buzzerPin, 1000);			//buzz high once
		delay(delayTime);						//wait
		softToneWrite(buzzerPin, 0);			//off

	}

};
/*
int main()										//buzzer test 
{
	wiringPiSetup();							//uses the wiringPi numbers for GPIO

	Buzzer buzz;	

	buzz.setupBuzzer();								//primes relevant pins for output use

	printf("Running Buzzer Test\n");

	buzz.startBasicRacingBuzzer();					//test basic method

	delay(1000);							//wait before next test
	printf("Running Advanced Buzzer Test\n");

	buzz.startRacingBuzzer();						//test advanced method


	return 0;
}
*/
