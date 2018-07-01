//Header file for LCD class, written by Stuart

#include <lcd.h> //LCD headers from WiringPi 

#define LCD_RS 29 //Register select pin 
#define LCD_E 28 //Enable Pin 
#define LCD_D4 25 //Data pin 4 
#define LCD_D5 27 //Data pin 5 
#define LCD_D6 21 //Data pin 6 
#define LCD_D7 22 //Data pin 7

class LCD { public:
	LCD()
	{
		lcd = lcdInit (2, 16, 4, LCD_RS, LCD_E, LCD_D4, LCD_D5, LCD_D6, LCD_D7, 0, 0, 0 ,0);
	}
	void lcdPrint1(std::string s)
	{
		const char * c = s.c_str();
		lcdPosition(lcd,0,0); //Position cursor on the first line in the first column
    		lcdPuts(lcd, c); //Print the text on the LCD at the current cursor postion
	}
	void lcdPrint2(std::string s)
	{
		const char * c = s.c_str();
		lcdPosition(lcd,0,1); //Position cursor on the first line in the first column
    		lcdPuts(lcd, c); //Print the text on the LCD at the current cursor postion
	}
	
	void clearLcd()
	{
		lcdClear(lcd);
	};
private:
	int lcd;
};
