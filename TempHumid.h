#include <wiringPi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string>
#define MAXTIMINGS	85
//This is Pin 13
#define DHTPIN		2 

//Code derived from: http://www.circuitbasics.com/how-to-set-up-the-dht11-humidity-sensor-on-the-raspberry-pi/

int dht11_dat[5] = { 0, 0, 0, 0, 0 };
float	f; 
int humidity = 0;

class DTH{
public:
DTH()
{
	temp = " ";
	hum = " ";
}
void read_dht11_dat()
{
	uint8_t laststate	= HIGH;
	uint8_t counter		= 0;
	uint8_t j		= 0, i;
	char * hum2 = NULL;
	char * temp2 = NULL;
 
	dht11_dat[0] = dht11_dat[1] = dht11_dat[2] = dht11_dat[3] = dht11_dat[4] = 0;
 
	pinMode( DHTPIN, OUTPUT );
	digitalWrite( DHTPIN, LOW );
	delay( 18 );
	digitalWrite( DHTPIN, HIGH );
	delayMicroseconds( 40 );
	pinMode( DHTPIN, INPUT );
	
 
	for ( i = 0; i < MAXTIMINGS; i++ )
	{
		counter = 0;
		while ( digitalRead( DHTPIN ) == laststate )
		{
			counter++;
			delayMicroseconds( 1 );
			if ( counter == 255 )
			{
				break;
			}
		}
		laststate = digitalRead( DHTPIN );
 
		if ( counter == 255 )
			break;
 
		if ( (i >= 4) && (i % 2 == 0) )
		{
			dht11_dat[j / 8] <<= 1;
			if ( counter > 16 )
				dht11_dat[j / 8] |= 1;
			j++;
		}
	}
	if ( (j >= 40) &&
	     (dht11_dat[4] == ( (dht11_dat[0] + dht11_dat[1] + dht11_dat[2] + dht11_dat[3]) & 0xFF) ) )
	{
		//printf("doing a thing");
		f = dht11_dat[2] * 9. / 5. + 32;
		humidity = dht11_dat[0];
		asprintf(&hum2, "Humidity = %d.%d", humidity, dht11_dat[1]);
		asprintf(&temp2, "Temp = %.1f F", f);
	}
	if (hum2 != NULL){
		//printf("hum\n");
		hum = hum2;
	}
	if (temp2 != NULL){
		//printf("temp\n");
		temp = temp2;
	}	
}

std::string returnTemp()
{
	std::string s(temp);
	return s;
}

float returnTempFloat()
{
	read_dht11_dat();
	return f;
}

int returnHumidityInt()
{
	read_dht11_dat();
	return humidity;
}

std::string returnHum()
{
	std::string s(hum);
	return s;
};


private:

	const char * temp = " ";
	const char * hum = " ";

};
