#include "sendmail.h"
#include "MCPReader.h" //local MCP3008 checking class]
#include <stdio.h> //Needed for the printf function below
//#include "dth.h"
//#include "fire.h"

SendMail sendMail;

float threshTemp = 90;
int threshHumid = 60;
int threshFlame = 650;
int threshSmoke = 350;

bool isAcceptTemp = true; // to allow emails to be sent only when temp crosses over threshold
bool isAcceptHumid = true; // to allow emails to be sent only when humidity crosses over threshold
bool isAcceptFlame = true; // to allow emails to be sent only when flame crosses over threshold
bool isAcceptSmoke = true; // to allow emails to be sent only when smoke crosses over threshold
bool allAcceptable = true;

class Poll
{
public:
	void pollTemp(DTH tempProbe) // can be safely polled often
	{
		std::cout << "current temp should be: " << tempProbe.returnTempFloat() << "\n";
		if ((isAcceptTemp) && (tempProbe.returnTempFloat() > threshTemp)) //if last known temp was acceptable and current temp is not, send notification of change
		{
			isAcceptTemp = false;
			printf("High temperatures detected.\n");
			sendMail.highTempEmail();
		}
		else if (tempProbe.returnTempFloat() <= threshTemp) //if last known temp was unacceptable and current temp is acceptable, send notification of change
		{
			isAcceptTemp = true;
			printf("Acceptable temperatures detected.\n");
			//sendMail.optimalTempEmail();
		}
	}

	void pollHumid(DTH tempProbe) // can be safely polled often
	{
		if ((isAcceptHumid) && (tempProbe.returnHumidityInt() > threshHumid)) //if last known humidity was acceptable and current humidity is not, send notification of change
		{
			isAcceptHumid = false;
			printf("High humidity detected.\n");
			sendMail.highHumidEmail();
		}
		else if ((!isAcceptHumid) && (tempProbe.returnHumidityInt() <= threshHumid)) //if last known humidity was unacceptable and current humidity is acceptable, send notification of change
		{
			isAcceptHumid = true;
			printf("Acceptable humidity levels detected.\n");
			//sendMail.optimalHumidEmail();
		}
	}

	void pollSmoke()
	{
		if (readSmoke() > threshSmoke)
		{
			printf("Smoke detected.\n");
			sendMail.smokeEmail();
			isAcceptSmoke = false;
		}
		else{
			isAcceptSmoke = true;
		}
	}

	void pollFire()
	{
		if (readIR() > threshFlame)
		{
			printf("Fire detected.\n");
			sendMail.fireEmail();
			isAcceptFlame = false;
		}
		else{
			isAcceptFlame = true;
		}
	}
	
	void pollAll(DTH tempProbe){
		printf("PollAll() should be running\n");
		pollTemp(tempProbe);
		pollHumid(tempProbe);
		pollSmoke();
		pollFire();
		
		if(isAcceptTemp && isAcceptFlame && isAcceptHumid && isAcceptSmoke)
			allAcceptable = true;
		else
			allAcceptable = false;
	}
	
	bool checkAcceptable(){
		return allAcceptable;
	}
};
