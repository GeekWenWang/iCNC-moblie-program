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
int mmiMain(MMI_DATA* mmiDataPtr)
{
	bool run = true;

	while(run)
	{
		switch(mmiDataPtr->mmiState)
		{
		case MMI_IDLE:
			mmiIdle(mmiDataPtr);
			break;

		case MEM_STATE:
			mmiMemState(mmiDataPtr);
			run = false;
			break;

		case JOG_STATE:
			mmiJogState(mmiDataPtr);
			run = false;
			break;

		case MMI_RESET:
			mmiReset(mmiDataPtr);
			run = false;
			break;

		default:
			break;

		}
	}//while

	return 1;
}//mmiMain
