#include "stdafx.h"


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "..\INC\cnc.h"   // dir can be absolute or relative
                          // abs: c:\program file\....

CNC_DATA          cncData;  // memory for CNC
CNC_DATA          *cncDataPtr = &cncData;

extern int clearByteSpace(char *startPtr, int size);
extern int decMain(DEC_DATA  *decDataPtr);
extern int decInit(DEC_DATA  *decDataPtr);

//******************************************************
//  main for non-real-time functions
//******************************************************
int nrtMain(CNC_DATA *cncDataPtr)
{
    if(cncDataPtr->mmiData.opMode == MEM_MODE)
	{
		mmiMain(&cncDataPtr->mmiData);
		linkMain(&cncDataPtr->linkData);
		decMain(&cncDataPtr->decData);
		linkMain(&cncDataPtr->linkData);
		//intpMain(&cncDataPtr->intpData);
	}
	else
	{
		return 1;
	}

   return 1;
} //nrtMain()



//******************************************************
//  main for real-time functions
//******************************************************
int rtMain(CNC_DATA *cncDataPtr)
{
	intpMain(&cncDataPtr->intpData);

   return 1;
} //rtMain()



//******************************************************
//
//******************************************************
int cncInit(void)
{
  	// clear decData
	clearByteSpace((char *)cncDataPtr, sizeof(CNC_DATA));
    mmiInit(&cncDataPtr->mmiData);
	decInit(&cncDataPtr->decData);
	intpInit(&cncDataPtr->intpData);
	// ...
	linkInit(&cncDataPtr->linkData);
   return 1;
} //cncInit()



//******************************************************
//
//******************************************************
int cncMain(CNC_DATA *cncDataPtr)
{
	if(cncDataPtr->mmiData.mmiState == MMI_RESET)
	{
		mmiMain(&cncDataPtr->mmiData);
	}
   return 1;
} //cncMain()
