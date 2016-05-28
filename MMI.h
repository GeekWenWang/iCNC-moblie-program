#ifndef _MMI_H
#define _MMI_H

#include <stdio.h>
#include <stdlib.h>

#include "..\..\UTINITY\INC\utinity.h"
enum OP_MODE{NULL_MODE,MEM_MODE,MDI_MODE,JOG_MODE};//operation mode define

enum MMI_STATE{MMI_IDLE , MEM_STATE , JOG_STATE ,MMI_RESET, MMI_CLOSE};


using namespace System;

struct mmiToDecData
{

};


struct MMI_DATA
{
	mmiToDecData *mmiToDecDataPtr;

	OP_MODE   opMode;       //Operation Mode
    MMI_STATE mmiState;

	int  counter;           //Timer Counter
	
	char ncFileName[200];
	bool START;
	bool RESET;

	bool ncFileValid;
	// bool serialCmdValid;

	double	CarCoordinate[3];
};

//*****************************
// function define
//*****************************
int mmiInit(MMI_DATA* mmiDataPtr);
int mmiMain(MMI_DATA* mmiDataPtr);
int mmiReset(MMI_DATA* mmiDataPtr);

int mmiIdle(MMI_DATA* mmiDataPtr);
int mmiMemState(MMI_DATA* mmiDataPtr);
int mmiJogState(MMI_DATA* mmiDataPtr);


#endif