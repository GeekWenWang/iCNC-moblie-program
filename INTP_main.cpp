#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>


#include "..\INC\INTP.h"
#include "..\..\CNC\INC\cnc.h"  // include user defined header file

extern CNC_DATA* cncDataPtr;




int intpMain(INTP_DATA *intpDataPtr)
{
	bool run = true;

	while(run)
	{
	
		switch(intpDataPtr->intpState)
		{
		case INTP_IDLE:
			intpIdle(intpDataPtr);
			break;

		case INTP_PRE:
			intpPre(intpDataPtr);
			break;


		case INTP_EXE:
			intpExe(intpDataPtr);
			if(intpDataPtr->lineCmd == NULL_CMD || intpDataPtr->intpState == INTP_DWELL_TIME )
			{
				run = true;
			}
			else
			{
				run = false;
			}
			break;

		case INTP_DWELL_TIME:
		countDownDwellTime(intpDataPtr);
		if(intpDataPtr->counter <= 0)
			{
				run = true;
			}
			else
			{
				run = false;
			}
		break;

		case INTP_CLOSE:
			intpClose(intpDataPtr);
			run = false;
			break;

		case INTP_ERROR:
			intpError(intpDataPtr);
			break;


		return 1;
		}
	}

	/*double time;
	
	time = intpDataPtr->xyCoordinate[0]/(intpDataPtr->speed);

	if(cncDataPtr->mmiData.counter < time)
	{
		intpDataPtr->serialCmd[0] = 50;
		intpDataPtr->serialCmd[1] = 40;
		intpDataPtr->serialCmd[2] = '!';
	}
	*/
	
	return 1;
}