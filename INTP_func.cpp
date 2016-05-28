#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>


#include "..\..\UTINITY\INC\utinity.h"
#include "..\INC\INTP.h"
#include "..\..\CNC\INC\cnc.h"  // include user defined header file

extern CNC_DATA* cncDataPtr;


int intpInit(INTP_DATA *intpDataPtr)
{
	intpDataPtr->intpState = INTP_NULL;
	intpDataPtr->cmdValid = false;
	intpDataPtr->lineNumber = 0 ; // N code
	intpDataPtr->lineNumberVaild = false;
	intpDataPtr->lineCmd = NULL_CMD;   // ensure that only one effective command!!
	intpDataPtr->lineCmdVaild = false;
	intpDataPtr->relAbs = false;    // false G90: abs,  true G91: rel
	intpDataPtr->relValid = false;
	intpDataPtr->xyCoordinate[0] = 0.0; // xy[0], xy[1]
	intpDataPtr->xyCoordinate[1] = 0.0;
	intpDataPtr->xyValid[0] = false; // reset at line begin
	intpDataPtr->angle = 0.0;
	intpDataPtr->direction = false;  // true: CW, false: CCW
	intpDataPtr->angleValid = false;
	intpDataPtr-> speed = 0.0;      //F
	intpDataPtr->dwellTime = 0.0; 
	intpDataPtr-> dwellValid = false;
	intpDataPtr-> speedValid = false;

	intpDataPtr->serialCmd[0] = 120;
	intpDataPtr->serialCmd[1] = '!';
	
	intpDataPtr->serialCmdValid = false;
	intpDataPtr->intpToLinkDataValid = false;

	for(int i=0; i<2; i++)
	{
	intpDataPtr->startPos[i] = 0.0;
	intpDataPtr->oldPos[i] = intpDataPtr->endPos[i];
	intpDataPtr->startPos[i] = intpDataPtr->oldPos[i];
	intpDataPtr->newPos[i] = 0.0;
	//back up one point

	intpDataPtr->relPos[i] = 0.0;
	}
	intpDataPtr->totalLength = 0.0;
	intpDataPtr-> sumLength = 0.0; //new distance
	intpDataPtr->residualLength = 0.0;//sumLength + residualLength = totalLength

	intpDataPtr->cyclingTime = 0.025;//period of real-time timer
	intpDataPtr->angularVelocity = 23.0;//degree per second

	intpDataPtr->totalAngle = 0.0;
	intpDataPtr->sumAngle = 0.0; //new distance
	intpDataPtr->residualAngle = 0.0;//sumAngle + residualAngle = totalAngle

	intpDataPtr->RESET = false;

	intpDataPtr->intpState = INTP_IDLE;


	return 1;
}

//******************************************************************************************
//
//******************************************************************************************

int intpIdle(INTP_DATA *intpDataPtr)
{
	//check if DEC_TO_INTP_BLOCK exists in LINK_DATA i.e. check if blockValid is true
	//if true, read, save, and reset blockValid to false
	//change state to INTP_PRE
	//else false do noting
	
	if(cncDataPtr->linkData.linkToIntpData.linkToIntpDataValid == true && cncDataPtr->linkData.linkToIntpData.cmdValid == true)
	{
		if(cncDataPtr->linkData.linkToIntpData.lineNumberVaild == true)
		{
			intpDataPtr->lineNumberVaild = cncDataPtr->linkData.linkToIntpData.lineNumberVaild;
			intpDataPtr->lineNumber = cncDataPtr->linkData.linkToIntpData.lineNumber;
			cncDataPtr->linkData.linkToIntpData.lineNumberVaild = false;
		}

		if(cncDataPtr->linkData.linkToIntpData.lineCmdVaild == true)
		{
			intpDataPtr->lineCmdVaild = cncDataPtr->linkData.linkToIntpData.lineCmdVaild;
			intpDataPtr->lineCmd = cncDataPtr->linkData.linkToIntpData.lineCmd;
			cncDataPtr->linkData.linkToIntpData.lineCmd = NULL_CMD;
			cncDataPtr->linkData.linkToIntpData.lineCmdVaild = false;
		}

		if(cncDataPtr->linkData.linkToIntpData.relValid == true)
		{
			intpDataPtr->relValid = cncDataPtr->linkData.linkToIntpData.relValid;
			intpDataPtr->relAbs = cncDataPtr->linkData.linkToIntpData.relAbs;
			cncDataPtr->linkData.linkToIntpData.relValid = false;
		}

		if(cncDataPtr->linkData.linkToIntpData.xyValid[0] == true || cncDataPtr->linkData.linkToIntpData.xyValid[1] == true)
		{
		    for(int i=0 ; i<2 ;i++)
			{
				if(cncDataPtr->linkData.linkToIntpData.xyValid[i] == true)
				{
					intpDataPtr->xyValid[i] = cncDataPtr->linkData.linkToIntpData.xyValid[i];
					intpDataPtr->xyCoordinate[i] = cncDataPtr->linkData.linkToIntpData.xyCoordinate[i];
					cncDataPtr->linkData.linkToIntpData.xyValid[0] = false;
				}
			}
			cncDataPtr->linkData.linkToIntpData.xyValid[1] = false;
		}

		if(cncDataPtr->linkData.linkToIntpData.angleValid == true)
		{
			intpDataPtr->angleValid = cncDataPtr->linkData.linkToIntpData.angleValid;
			
			intpDataPtr->angle = cncDataPtr->linkData.linkToIntpData.angle;
			intpDataPtr->direction = cncDataPtr->linkData.linkToIntpData.direction;

			cncDataPtr->linkData.linkToIntpData.angleValid = false;
		}

		if(cncDataPtr->linkData.linkToIntpData.speedValid == true)
		{
			intpDataPtr->speedValid = cncDataPtr->linkData.linkToIntpData.speedValid;
			intpDataPtr->speed = cncDataPtr->linkData.linkToIntpData.speed;
			cncDataPtr->linkData.linkToIntpData.speedValid = false;
		}

		if(cncDataPtr->linkData.linkToIntpData.dwellValid == true)
		{
			intpDataPtr->dwellValid = cncDataPtr->linkData.linkToIntpData.dwellValid;
			intpDataPtr->dwellTime = cncDataPtr->linkData.linkToIntpData.dwellTime;
			cncDataPtr->linkData.linkToIntpData.dwellValid = false;
		}

		intpDataPtr->cmdValid = cncDataPtr->linkData.linkToIntpData.cmdValid ;

		cncDataPtr->linkData.linkToIntpData.cmdValid = false;
		cncDataPtr->linkData.linkToIntpData.linkToIntpDataValid = false;
		intpDataPtr->intpState = INTP_PRE;

	}//if(cncDataPtr->linkData.linkToIntpData.cmdValid = true)
	
	//code for explain the varibles to serialport and counter => carCoordinate
	

	return 1;
}

//******************************************************************************************
//
//******************************************************************************************

int intpPre(INTP_DATA *intpDataPtr)
{
	//G00, G06 ,G07 
	
	
	//{G00_CMD,G04_DWELL_TIME,G06_ROT_CW,G07_ROT_CCW,M30_PROG_END,NULL_CMD}

	switch(intpDataPtr->lineCmd)
	{
	case G00_CMD://point to point information
		//start new old end point
		//cauculate parameter for interpolation
		//see and reset motion parameter
		//linear factor = relLength/totalLength
		
		for(int i=0; i<2; i++)
		{
			intpDataPtr->startPos[i] = intpDataPtr->endPos[i];//上次的endPos
		}
		
		for(int i=0; i<2; i++)
		{
			intpDataPtr->endPos[i] = intpDataPtr->xyCoordinate[i];
		}

		//if(intpDataPtr->endPos[0]-intpDataPtr->startPos[0] !=0)
		//{
			//intpDataPtr->headPointer = atan((intpDataPtr->endPos[1]-intpDataPtr->startPos[1])/(intpDataPtr->endPos[0]-intpDataPtr->startPos[0]))/3.14*180;
		//}
		//else
		//{
			//intpDataPtr->headPointer = 90;
		//}
	
		intpDataPtr->totalLength = sqrt(pow(((intpDataPtr->endPos[0])-(intpDataPtr->startPos[0])), 2) + pow(((intpDataPtr->endPos[1])-(intpDataPtr->startPos[1])), 2));
		intpDataPtr->deltaLength = (intpDataPtr->speed) * (intpDataPtr->cyclingTime);


		intpDataPtr->intpState = INTP_EXE;

		break;

	case G04_DWELL_TIME:
		
		
		for(int i=0; i<2; i++)
		{
			intpDataPtr->startPos[i] = intpDataPtr->endPos[i];//上次的endPos
		}
		
		for(int i=0; i<2; i++)
		{
			intpDataPtr->endPos[i] = intpDataPtr->xyCoordinate[i];
		}

		intpDataPtr->intpState = INTP_EXE;

		break;

	case G06_ROT_CW:

		for(int i=0; i<2; i++)
		{
			intpDataPtr->startPos[i] = intpDataPtr->endPos[i];//上次的endPos
		}
		
		for(int i=0; i<2; i++)
		{
			intpDataPtr->endPos[i] = intpDataPtr->xyCoordinate[i];
		}

		//intpDataPtr->headPointer = intpDataPtr->absAngle;

		intpDataPtr->deltaAngle = (intpDataPtr->cyclingTime)*(intpDataPtr->angularVelocity);

		intpDataPtr->intpState = INTP_EXE;

		break;

	case G07_ROT_CCW:

		for(int i=0; i<2; i++)
		{
			intpDataPtr->startPos[i] = intpDataPtr->endPos[i];//上次的endPos
		}
		
		for(int i=0; i<2; i++)
		{
			intpDataPtr->endPos[i] = intpDataPtr->xyCoordinate[i];
		}

		//intpDataPtr->headPointer = intpDataPtr->absAngle;

		intpDataPtr->deltaAngle = (intpDataPtr->cyclingTime)*(intpDataPtr->angularVelocity);

		intpDataPtr->intpState = INTP_EXE;

		break;

	case M30_PROG_END:

		for(int i=0; i<2; i++)
		{
			intpDataPtr->startPos[i] = intpDataPtr->endPos[i];//上次的endPos
		}
		
		for(int i=0; i<2; i++)
		{
			intpDataPtr->endPos[i] = intpDataPtr->xyCoordinate[i];
		}

		//intpDataPtr->headPointer = intpDataPtr->absAngle;

		intpDataPtr->deltaAngle = (intpDataPtr->cyclingTime)*(intpDataPtr->angularVelocity);

		intpDataPtr->intpState = INTP_CLOSE;



		break;



	}

	return 1;
}

//******************************************************************************************
//
//******************************************************************************************

int intpExe(INTP_DATA *intpDataPtr)
{
	//generate new point on the path(startPos to endPos)
	//sumLength = sumLength + speed*intp cyclingTime
	//oldPos = newPos do back up
	//newPos = startPos +sumLength* linearFactor(deltaX/totalLength or deltaY/totalLength斜率) chech ok
	
	//send to arduino via serial port

	//determine if motion is to end in next cycle
	//yes change state to INTP_CLOSE

	if(intpDataPtr->lineCmd == G00_CMD)
	{
		double deltaX;
		double deltaY;

		deltaX = ((intpDataPtr->endPos[0])-(intpDataPtr->startPos[0]));
		deltaY = ((intpDataPtr->endPos[1])-(intpDataPtr->startPos[1]));

		double linearFactor[2];

		linearFactor[0] = deltaX/(intpDataPtr->totalLength);
		linearFactor[1] = deltaY/(intpDataPtr->totalLength);
		
		for(int i=0; i<2; i++)
		{
			intpDataPtr->newPos[i] = intpDataPtr->oldPos[i];
		}


		intpDataPtr->newPos[0] = intpDataPtr->oldPos[0] + (intpDataPtr->deltaLength)*linearFactor[0] ;
		intpDataPtr->newPos[1] = intpDataPtr->oldPos[1] + (intpDataPtr->deltaLength)*linearFactor[1] ;

		for(int i=0 ; i<2 ;i++)
		{
			intpDataPtr->oldPos[i] = intpDataPtr->newPos[i];
			intpDataPtr->carCoordinate[i] = intpDataPtr->oldPos[i];
		}

		intpDataPtr->sumLength = intpDataPtr->sumLength + intpDataPtr->deltaLength;
		intpDataPtr->residualLength = (intpDataPtr->totalLength)-(intpDataPtr->sumLength);

		if(intpDataPtr->oldPos[0] != 0)
		{
			intpDataPtr->absAngle = atan(intpDataPtr->oldPos[1]/intpDataPtr->oldPos[0])/3.14*180;
			intpDataPtr->carCoordinate[2] = intpDataPtr->absAngle;
		}
		else
		{
			intpDataPtr->absAngle = 90;
			intpDataPtr->carCoordinate[2] = intpDataPtr->absAngle;
		}

		if(intpDataPtr->serialCmdValid == false)
		{
			intpDataPtr->serialCmd[0] = 54;
			intpDataPtr->serialCmd[1] = '!';
			intpDataPtr->serialCmdValid = true;
		}

		

		if(intpDataPtr->residualLength <= intpDataPtr->deltaLength)
		{
			intpDataPtr->intpState = INTP_CLOSE;
		}

		
	}

	else if(intpDataPtr->lineCmd == G04_DWELL_TIME)
	{
		intpDataPtr->counter = 0;
		intpDataPtr->counter = (int)intpDataPtr->dwellTime/30;
		
		intpDataPtr->intpState = INTP_DWELL_TIME;
		//在這裡不可以寫 intpDataPtr->lineCmd = NULL_CMD;
		//系統會發瘋 把nrtime關了 害我debug 快5小時
		
	}

	else if(intpDataPtr->lineCmd == G06_ROT_CW)
	{
		intpDataPtr->sumAngle = (intpDataPtr->sumAngle)+(intpDataPtr->deltaAngle);
		
		if(intpDataPtr->carCoordinate[0] != 0)
		{
			intpDataPtr->absAngle = atan(intpDataPtr->carCoordinate[1]/intpDataPtr->carCoordinate[0])/3.14*180;
		}
		else
		{
			intpDataPtr->absAngle = 90 ;
		}
		
		intpDataPtr->headPointer = (intpDataPtr->headPointer)-(intpDataPtr->deltaAngle);
		intpDataPtr->carCoordinate[2] = intpDataPtr->absAngle;
		
		intpDataPtr->residualAngle = (intpDataPtr->angle) - (intpDataPtr->sumAngle);

		if(intpDataPtr->serialCmdValid == false)
		{
			intpDataPtr->serialCmd[0] = 119;
			intpDataPtr->serialCmd[1] = '!';
			intpDataPtr->serialCmdValid = true;
		}

		if(intpDataPtr->residualAngle <= (intpDataPtr->deltaAngle))
		{
			intpDataPtr->intpState = INTP_CLOSE;
		}
		
	}

	else if(intpDataPtr->lineCmd == G07_ROT_CCW)
	{
		intpDataPtr->sumAngle = (intpDataPtr->sumAngle)+(intpDataPtr->deltaAngle);
		
		if(intpDataPtr->carCoordinate[0] != 0)
		{
			intpDataPtr->absAngle = atan(intpDataPtr->carCoordinate[1]/intpDataPtr->carCoordinate[0])/3.14*180;
		}
		else
		{
			intpDataPtr->absAngle = 90 ;
		}

		intpDataPtr->headPointer = (intpDataPtr->headPointer)+(intpDataPtr->deltaAngle);
		intpDataPtr->carCoordinate[2] = intpDataPtr->absAngle;
		
		intpDataPtr->residualAngle = (intpDataPtr->angle) - (intpDataPtr->sumAngle);

		if(intpDataPtr->serialCmdValid == false)
		{
			intpDataPtr->serialCmd[0] = 118;
			intpDataPtr->serialCmd[1] = '!';
			intpDataPtr->serialCmdValid = true;
		}

		if(intpDataPtr->residualAngle <= (intpDataPtr->deltaAngle))
		{
			intpDataPtr->intpState = INTP_CLOSE;
		}
	}

	return 1;
}

//******************************************************************************************
//
//******************************************************************************************

int intpClose(INTP_DATA *intpDataPtr)
{
	//newPos  = endPos
	//send to arduino via serial port
	//change state to INTP_IDLE
	
	if(intpDataPtr->lineCmd == G00_CMD)
	{
		for(int i =0; i<2 ; i++)
		{
		intpDataPtr->oldPos[i] = intpDataPtr->newPos[i];
		intpDataPtr->newPos[i] = intpDataPtr->endPos[i];
		intpDataPtr->endPos[i] = intpDataPtr->carCoordinate[i];
		}
		if(intpDataPtr->carCoordinate[0] != 0)
		{
			intpDataPtr->absAngle = atan(intpDataPtr->carCoordinate[1]/intpDataPtr->carCoordinate[0])/3.14*180;
		}
		else
		{
			intpDataPtr->absAngle = 90 ;
		}
		intpDataPtr->carCoordinate[2] = intpDataPtr->absAngle;
		if(intpDataPtr->serialCmdValid == false)
		{
			intpDataPtr->serialCmd[0] = 120;
			intpDataPtr->serialCmd[1] = '!';
			intpDataPtr->serialCmdValid = true;
		}
	}

		if(intpDataPtr->lineCmd == G04_DWELL_TIME)
	{
		for(int i =0; i<2 ; i++)
		{
		intpDataPtr->oldPos[i] = intpDataPtr->newPos[i];
		intpDataPtr->newPos[i] = intpDataPtr->endPos[i];
		intpDataPtr->endPos[i] = intpDataPtr->carCoordinate[i];
		}
		if(intpDataPtr->carCoordinate[0] != 0)
		{
			intpDataPtr->absAngle = atan(intpDataPtr->carCoordinate[1]/intpDataPtr->carCoordinate[0])/3.14*180;
		}
		else
		{
			intpDataPtr->absAngle = 90 ;
		}
		intpDataPtr->carCoordinate[2] = intpDataPtr->absAngle;
		if(intpDataPtr->serialCmdValid == false)
		{
			intpDataPtr->serialCmd[0] = 120;
			intpDataPtr->serialCmd[1] = '!';
			intpDataPtr->serialCmdValid = true;
		}
	}



	if(intpDataPtr->lineCmd == G06_ROT_CW)
	{
		for(int i =0; i<2 ; i++)
		{
		intpDataPtr->oldPos[i] = intpDataPtr->newPos[i];
		intpDataPtr->newPos[i] = intpDataPtr->endPos[i];
		intpDataPtr->endPos[i] = intpDataPtr->carCoordinate[i];
		}
		if(intpDataPtr->carCoordinate[0] != 0)
		{
			intpDataPtr->absAngle = atan(intpDataPtr->carCoordinate[1]/intpDataPtr->carCoordinate[0])/3.14*180;
		}
		else
		{
			intpDataPtr->absAngle = 90 ;
		}
		
		intpDataPtr->absAngle = (intpDataPtr->absAngle)-(intpDataPtr->angle);
		intpDataPtr->carCoordinate[2] = intpDataPtr->absAngle;
		
		if(intpDataPtr->serialCmdValid == false)
		{
			intpDataPtr->serialCmd[0] = 120;
			intpDataPtr->serialCmd[1] = '!';
			intpDataPtr->serialCmdValid = true;
		}
	}

	if(intpDataPtr->lineCmd == G07_ROT_CCW)
	{
		for(int i =0; i<2 ; i++)
		{
		intpDataPtr->oldPos[i] = intpDataPtr->newPos[i];
		intpDataPtr->newPos[i] = intpDataPtr->endPos[i];
		intpDataPtr->endPos[i] = intpDataPtr->carCoordinate[i];
		}
		
		if(intpDataPtr->carCoordinate[0] != 0)
		{
			intpDataPtr->absAngle = atan(intpDataPtr->carCoordinate[1]/intpDataPtr->carCoordinate[0])/3.14*180;
		}
		else
		{
			intpDataPtr->absAngle = 90 ;
		}

		intpDataPtr->absAngle = (intpDataPtr->absAngle)+(intpDataPtr->angle);
		intpDataPtr->carCoordinate[2] = intpDataPtr->absAngle;

		if(intpDataPtr->serialCmdValid == false)
		{
			intpDataPtr->serialCmd[0] = 120;
			intpDataPtr->serialCmd[1] = '!';
			intpDataPtr->serialCmdValid = true;
		}
	}

	if(intpDataPtr->lineCmd == M30_PROG_END)
	{
		if(intpDataPtr->serialCmdValid == false)
		{
			intpDataPtr->serialCmd[0] = 120;
			intpDataPtr->serialCmd[1] = '!';
			intpDataPtr->serialCmdValid = true;
		}
		
		return 1;
	}
	
	
	intpDataPtr->lineCmd = NULL_CMD;
	 
	intpInit(intpDataPtr);

   intpDataPtr->intpState = INTP_IDLE;


	return 1;
}

//******************************************************************************************
//
//******************************************************************************************

int intpError(INTP_DATA *intpDataPtr)
{


	return 1;
}


//******************************************************************************************
//
//******************************************************************************************
int countDownDwellTime(INTP_DATA *intpDataPtr)
{

	intpDataPtr->counter =  intpDataPtr->counter -1;
	if(intpDataPtr->counter <= 0.3)
	{
		intpDataPtr->intpState = INTP_CLOSE;
		return 1;
	}
	else
	{
		if(intpDataPtr->serialCmdValid == false)
		{
			intpDataPtr->serialCmd[0] = 120;
			intpDataPtr->serialCmd[1] = '!';
			intpDataPtr->serialCmdValid = true;
		}
		return 1;
	}
	
}

//************************************************************************************************
//
//*************************************************************************************************

