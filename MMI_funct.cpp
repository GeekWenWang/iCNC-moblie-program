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
int mmiInit(MMI_DATA* mmiDataPtr)
{
	clearByteSpace((char *)mmiDataPtr, sizeof(MMI_DATA));
	if(!mmiDataPtr)
	{
		return 0;
	}

	mmiDataPtr->mmiState = MMI_IDLE;
	mmiDataPtr->opMode = NULL_MODE;

	mmiDataPtr->START = false;
	mmiDataPtr->RESET = false;

	mmiDataPtr->ncFileValid = false;
	// mmiDataPtr->serialCmdValid = false;

	for(int i = 0 ; i < 3 ; i++)
	{
		mmiDataPtr->CarCoordinate[i] = 0.0;
	}

	for(int i = 0 ; i < 200 ; i++)
	{
		mmiDataPtr->ncFileName[i] = '\0';
	}

	mmiDataPtr->counter = 0;

	return 1;
}


//*********************************************************
//
//*********************************************************
int mmiIdle(MMI_DATA* mmiDataPtr)
{
	//HW: check START & RESET button from FORM, than sand result to  mmiToLinkData.
	if(mmiDataPtr->START == true)
	{
		//sand result
		cncDataPtr->linkData.mmiToLinkData.START = true;
		mmiDataPtr->START = false;
	}
	if(mmiDataPtr->RESET == true)
	{
		//if RESET, change mmiState.
		mmiDataPtr->mmiState = MMI_RESET;
		//sand result
		cncDataPtr->linkData.mmiToLinkData.RESET = true;
		return 0;
		
	}

	mmiDataPtr->CarCoordinate[0] = cncDataPtr->linkData.linkToMmiData.CarCoordinate[0];
	mmiDataPtr->CarCoordinate[1] = cncDataPtr->linkData.linkToMmiData.CarCoordinate[1];
	mmiDataPtr->CarCoordinate[2] = cncDataPtr->linkData.linkToMmiData.CarCoordinate[2];
	
	switch(mmiDataPtr->opMode)
	{
	case MEM_MODE:
		mmiDataPtr->mmiState = MEM_STATE;
		break;

	case JOG_MODE:
		mmiDataPtr->mmiState = JOG_STATE;
		break;

	default:
		break;
	}

	return 1;
}

//*********************************************************
//
//*********************************************************
int mmiMemState(MMI_DATA* mmiDataPtr)
{
	//HW: check ncFileValid, change bool, and send information to linkToMmiData.
	if(mmiDataPtr->ncFileValid == true)
	{

		//if true, copy the file path to linkToMmiData using strcpy.
		strcpy(cncDataPtr->linkData.mmiToLinkData.ncFileName , mmiDataPtr->ncFileName);
		mmiDataPtr->ncFileValid = false;
		//send result
		cncDataPtr->linkData.mmiToLinkData.ncFileValid = true;
		
		cncDataPtr->linkData.mmiToLinkData.mmiToLinkDataValid = true; //DEC can read
		
	}


	mmiDataPtr->mmiState = MMI_IDLE;

	return 1;
}



//*********************************************************
//
//*********************************************************
int mmiJogState(MMI_DATA* mmiDataPtr)
{
	mmiDataPtr->mmiState = MMI_IDLE;

	return 1;
}

//*********************************************************
//
//*********************************************************
int mmiReset(MMI_DATA* mmiDataPtr)
{
	//reset all mmiData
	if(mmiDataPtr->RESET == true)
	{
		cncInit();
	
		for(int i=0 ;i<3; i++)
		{
			cncDataPtr->intpData.carCoordinate[i] = 0.0;
		}

		for(int i=0 ;i<2; i++)
		{
			cncDataPtr->intpData.xyCoordinate[i] = 0.0;
		}	

		cncDataPtr->intpData.absAngle = 0.0;

		mmiDataPtr->RESET = false;
	}
	return 1;
}
