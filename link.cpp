#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "..\..\UTINITY\INC\utinity.h"
#include "..\..\CNC\INC\cnc.h"

extern CNC_DATA* cncDataPtr;

//*********************************************************
//
//*********************************************************
int linkInit(LINK_DATA* linkDataPtr)
{
	clearByteSpace((char *) linkDataPtr , sizeof(LINK_DATA));
	mmiToLinkDataInit(linkDataPtr);
	linkToMmiDataInit(linkDataPtr);
	decToLinkDataInit(linkDataPtr);
	linkToDecDataInit(linkDataPtr);
	intpToLinkDataInit(linkDataPtr);
	linkToIntpDataInit(linkDataPtr);

	return 1;
}

//*********************************************************
//
//*********************************************************
int mmiToLinkDataInit(LINK_DATA* linkDataPtr)
{
	for(int i = 0 ; i < 200 ; i++)
	{

		linkDataPtr->mmiToLinkData.ncFileName[i] = '\0';
	}


	linkDataPtr->mmiToLinkData.ncFileValid = false;
	linkDataPtr->mmiToLinkData.RESET = false;

	return 1;
}

//*********************************************************
//
//*********************************************************
int linkToMmiDataInit(LINK_DATA* linkDataPtr)
{
	linkDataPtr->linkToMmiData.counter = 0;

	for(int i = 0 ; i < 3 ; i++)
	{
		linkDataPtr->linkToMmiData.CarCoordinate[i] = 0.0;
	}

	for(int i = 0 ; i < 4 ; i++)
	{
		linkDataPtr->linkToMmiData.serialCmd[i] = '\0';
	}


	linkDataPtr->linkToMmiData.serialCmdVaild = false;

	return 1;
}

//*********************************************************
//
//*********************************************************
int decToLinkDataInit(LINK_DATA* linkDataPtr)
{
	//linkDataPtr->decToLinkBlock.cmdVaild = false;
	//linkDataPtr->decToLinkBlock.lineNumber = 0;
	linkDataPtr->decToLinkBlock.lineNumberValid = false;
	//linkDataPtr->decToLinkBlock.lineCmd = 0;
	//linkDataPtr->decToLinkBlock.lineCmdVaild = false;
	linkDataPtr->decToLinkBlock.relAbs = false;
	linkDataPtr->decToLinkBlock.relValid = false;

	for(int i = 0 ; i < 2 ; i++)
	{
		linkDataPtr->decToLinkBlock.xyCoordinate[i] = 0.0;
		linkDataPtr->decToLinkBlock.xyValid[i] = false;
	}

	linkDataPtr->decToLinkBlock.angle = 0.0;
	linkDataPtr->decToLinkBlock.direction = false;
	linkDataPtr->decToLinkBlock.angleValid = false;
	linkDataPtr->decToLinkBlock.speed = 0.0;
	linkDataPtr->decToLinkBlock.speedValid = false;
	linkDataPtr->decToLinkBlock.dwellValid = false;

	return 1;
}

//*********************************************************
//
//*********************************************************
int linkToDecDataInit(LINK_DATA* linkDataPtr)
{
	for(int i = 0 ; i < 200 ; i++)
	{
		linkDataPtr->linkToDecData.ncFileName[i] = '\0';

	}

	linkDataPtr->linkToDecData.ncFileValid = false;
	linkDataPtr->linkToDecData.RESET = false;
	linkDataPtr->linkToDecData.START = false;

	return 1;
}

//*********************************************************
//
//*********************************************************
int intpToLinkDataInit(LINK_DATA* linkDataPtr)
{
	for(int i = 0 ; i < 3 ; i++)
	{
		linkDataPtr->intpToLinkData.CarCoordinate[i] = 0.0;
	}

	for(int i = 0 ; i < 4 ; i++)
	{
		linkDataPtr->intpToLinkData.serialCmd[i] = '\0';
	}

	linkDataPtr->intpToLinkData.serialCmdVaild = false;

	linkDataPtr->intpToLinkData.RESET = false;

	return 1;
}

//*********************************************************
//
//*********************************************************
int linkToIntpDataInit(LINK_DATA* linkDataPtr)
{
	linkDataPtr->linkToIntpData.cmdValid = false;
	linkDataPtr->linkToIntpData.lineNumber = 0;
	linkDataPtr->linkToIntpData.lineNumberVaild = false;
	//linkDataPtr->linkToIntpData.lineCmd = 0;
	linkDataPtr->linkToIntpData.lineCmdVaild = false;
	linkDataPtr->linkToIntpData.relAbs = false;
	linkDataPtr->linkToIntpData.relValid = false;

	for(int i = 0 ; i < 2 ; i++)
	{
		linkDataPtr->linkToIntpData.xyCoordinate[i] = 0.0;
		linkDataPtr->linkToIntpData.xyValid[i] = false;
	}

	linkDataPtr->linkToIntpData.angle = 0.0;
	linkDataPtr->linkToIntpData.direction = false;
	linkDataPtr->linkToIntpData.angleValid = false;
	linkDataPtr->linkToIntpData.dwellTime = 0.0;
	linkDataPtr->linkToIntpData.dwellValid = false;
	linkDataPtr->linkToIntpData.speedValid = false;

	return 1;
}
//*********************************************************
//
//*********************************************************
int linkMain(LINK_DATA* linkDataPtr)
{
	if(linkDataPtr->mmiToLinkData.mmiToLinkDataValid == true )
	{
	
		linkDataPtr->linkToDecData.linkToDecDataValid = linkDataPtr->mmiToLinkData.mmiToLinkDataValid;
		
		if(linkDataPtr->mmiToLinkData.ncFileValid == true )
		{
			linkDataPtr->linkToDecData.ncFileValid = linkDataPtr->mmiToLinkData.ncFileValid;
			strcpy(linkDataPtr->linkToDecData.ncFileName,linkDataPtr->mmiToLinkData.ncFileName);
			linkDataPtr->mmiToLinkData.ncFileValid= false;
		}

		linkDataPtr->linkToDecData.START=linkDataPtr->mmiToLinkData.START ;
		linkDataPtr->linkToDecData.RESET=linkDataPtr->mmiToLinkData.RESET ;
		linkDataPtr->mmiToLinkData.mmiToLinkDataValid = false;
	}

	//link to dec => dec to intp
	
	if(linkDataPtr->decToLinkBlock.lineNumberValid == true)//N command
		{
			linkDataPtr->linkToIntpData.lineNumber = linkDataPtr->decToLinkBlock.Ncommand;
			linkDataPtr->linkToIntpData.lineNumberVaild = linkDataPtr->decToLinkBlock.lineNumberValid;
			linkDataPtr->decToLinkBlock.lineNumberValid = false;
		}
	
	
	
	
	if(linkDataPtr->decToLinkBlockValid == true)
	{
		if(linkDataPtr->decToLinkBlock.lineCmdValid == true)
		{
			linkDataPtr->linkToIntpData.lineCmd = linkDataPtr->decToLinkBlock.lineCmd;
			linkDataPtr->linkToIntpData.lineCmdVaild = linkDataPtr->decToLinkBlock.lineCmdValid;
			linkDataPtr->decToLinkBlock.lineCmdValid = false;
		}	
		if(linkDataPtr->decToLinkBlock.relValid == true)//G90 91
		{
			linkDataPtr->linkToIntpData.relAbs = linkDataPtr->decToLinkBlock.relAbs;
			linkDataPtr->linkToIntpData.relValid = linkDataPtr->decToLinkBlock.relValid;
			linkDataPtr->decToLinkBlock.relValid = false;
		}

		if(linkDataPtr->decToLinkBlock.xyValid[0] == true || linkDataPtr->decToLinkBlock.xyValid[1] == true)
		{
			for(int i=0 ; i<2 ;i++)
			{
				if(linkDataPtr->decToLinkBlock.xyValid[i] == true)
				{
					linkDataPtr->linkToIntpData.xyValid[i] = linkDataPtr->decToLinkBlock.xyValid[i];
					linkDataPtr->linkToIntpData.xyCoordinate[i] = linkDataPtr->decToLinkBlock.xyCoordinate[i];
					linkDataPtr->decToLinkBlock.xyValid[0] = false;
				}
			}
			linkDataPtr->decToLinkBlock.xyValid[1] = false;
		}

		if(linkDataPtr->decToLinkBlock.angleValid ==true)
		{
			linkDataPtr->linkToIntpData.angleValid = linkDataPtr->decToLinkBlock.angleValid;

			linkDataPtr->linkToIntpData.direction = linkDataPtr->decToLinkBlock.direction;
			linkDataPtr->linkToIntpData.angle = linkDataPtr->decToLinkBlock.angle;

			linkDataPtr->decToLinkBlock.angleValid = false;
		}

		if(linkDataPtr->decToLinkBlock.speedValid == true)
		{
			linkDataPtr->linkToIntpData.speedValid = linkDataPtr->decToLinkBlock.speedValid;
			linkDataPtr->linkToIntpData.speed = linkDataPtr->decToLinkBlock.speed;
			linkDataPtr->decToLinkBlock.speedValid = false;
		}

		if(linkDataPtr->decToLinkBlock.dwellValid == true)
		{
			linkDataPtr->linkToIntpData.dwellValid = linkDataPtr->decToLinkBlock.dwellValid;
			linkDataPtr->linkToIntpData.dwellTime = linkDataPtr->decToLinkBlock.dwellTime;
			linkDataPtr->decToLinkBlock.dwellValid = false;
		}

		
		linkDataPtr->linkToIntpData.linkToIntpDataValid = linkDataPtr->decToLinkBlockValid;
		linkDataPtr->decToLinkBlockValid = false;
		
		linkDataPtr->linkToIntpData.cmdValid = true;
	}

	
		return 0;
}