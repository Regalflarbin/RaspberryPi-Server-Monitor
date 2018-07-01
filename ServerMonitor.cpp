#include <wiringPi.h> //WiringPi headers 
#include <stdio.h> //Needed for the printf function below
#include <iostream> 
#include <string> //Pin numbers below are the WiringPi pin numbers
#include "lcd.h" //local lcd class
//#include "MCPReader.h" //local MCP3008 checking class
#include <sstream> //string stream for printing sensor to LCD
#include "TempHumid.h" 
#include "poll.h"
#include <softTone.h>

void updateLCD(LCD, DTH);

int current_temp, current_humidity, current_smoke, current_flame;
int buzzerPin = 23;
bool buzzerHigh = false;

Poll poll;
int main() {
    printf("Get launch!\n");
	wiringPiSetup(); //Initialise WiringPi
	spiSetup(); //setup SPI to read from MCP
	LCD lcd; //init LCD object defined in lcd.h
	DTH tempProbe; //init tempProbe object defined in TempHumid.h
	pinMode(buzzerPin, OUTPUT);
	softToneCreate(buzzerPin);
	

    std::cout<< "Smoke Sensor: " << readSmoke() << "\n";
    std::cout<< "IR Sensor: " << readIR() << "\n";
	
	Poll poll;
	
	while(true){
		poll.pollAll(tempProbe);
		std::cout << "Temp is: " << tempProbe.returnTempFloat() << "\n";
		std::cout << "Humidity is: " << tempProbe.returnHumidityInt() << "\n";
		std::cout << "Acceptable: " << poll.checkAcceptable() << "\n";
		//Reads in current flame and smoke sensor data from MCPReader.h methods
		current_flame = readIR();
		current_smoke = readSmoke();
		
		//Sound buzzer (alternatingly high and low) if thresholds exceeded. Turns buzzer off if all clear
		if(poll.checkAcceptable()){
			softToneWrite(buzzerPin, 0);
		}
		else{
			if(buzzerHigh){
				softToneWrite(buzzerPin,1000);
				buzzerHigh = false;
			}
			else{
				softToneWrite(buzzerPin,500);
				buzzerHigh = true;
			}
		}
		
		updateLCD(lcd, tempProbe);
	}
	
	return 0;
}

//Display smoke and IR, then alternate to temp and humidity after two seconds
void updateLCD(LCD lcd, DTH tempProbe){
	//New string stream for each line, can be "printed" to from many data types
	std::ostringstream line1;
	std::ostringstream line2;
	std::ostringstream line3;
	std::ostringstream line4;
	//Assigns value of each line by "printing" to it
	line1 << "Smoke: " << current_smoke;
	line2 << "Flame: " << current_flame;
	tempProbe.read_dht11_dat();
	//line3 << tempProbe.returnHum().c_str();
	//line4 << tempProbe.returnTemp().c_str();
	line3 << "Temp: " << tempProbe.returnTempFloat();
	line4 << "Humidity: " << tempProbe.returnHumidityInt();
	
	//Clears LCD, prints line 1 and 2, then does the same two seconds later for line 3 and 4
	lcd.clearLcd();
	lcd.lcdPrint1(line1.str());
	lcd.lcdPrint2(line2.str());
	delay(2000);
	lcd.clearLcd();
	lcd.lcdPrint1(line3.str());
	lcd.lcdPrint2(line4.str());
	delay(2000);
	
}
