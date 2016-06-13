#include "stdafx.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "..\..\LINK\IRC\link.h"
#include "..\INC\Dec.h"
#include "..\..\UTINITY\INC\utinity.h"

#include "..\..\CNC\INC\cnc.h"  // include user defined header file

extern CNC_DATA* cncDataPtr;

#define CHAR_IN_LINE_MAX 200

int decMain(DEC_DATA  *decDataPtr); 

// functions outside the cpp file
// extern int decInit(DEC_DATA  *decDataPtr);

//***********************************************************
//  main 
//***********************************************************


//***********************************************************
// dec main loop
//***********************************************************
int decMain(DEC_DATA  *decDataPtr)
{
  bool run = true;


  while(run)
  {
	// state machine state, action, transition condition
   switch (decDataPtr->decState)
   {
       case DEC_INIT:
	      decInit(decDataPtr);
	      break;
	   case DEC_IDLE:
		   decIdle(decDataPtr);
		   break;
	   case DEC_OPEN_FILE:
		   decOpenFile(decDataPtr);
		   break;
	   case DEC_LOOP:
		   decLoop(decDataPtr);
		   if(decDataPtr->asciiPtr[0] == '\0')
		   {
			   run = false;
		   }
		   break; 
	   case DEC_WRITE_OUT:
		   decWriteOut(decDataPtr);
		   run = false;
		   break;
	   case DEC_WAIT_M30:
		   decWaitM30(decDataPtr);
		   break;
	   case DEC_ERROR:
		   decError(decDataPtr);
		   break;
   } // switch
     
  }
   return 1;
} //decMain() 

//*************************************************************************************
//
//*************************************************************************************
int decInit(DEC_DATA  *decDataPtr)
{
	// clear decData
  /*clearDataByte((char *)decDataPtr, sizeof(DEC_DATA));*/

  for (int i=0; i < CHAR_IN_LINE_MAX ; i++)
   {
      decDataPtr->ncLine[i] = 0;
   }

 // exlicitly init some variables
    decDataPtr->asciiPtr = &decDataPtr->ncLine[0];    // init asciiPtr

	for(int i=0 ;i<2 ;i++)
	{
	decDataPtr->startPos.xyCoordinate[i] = 0;
	}
	// extension for mobile car !!! 
	decDataPtr->markN = false;
	decDataPtr->markG00 = false;
	decDataPtr->markG90 = false;
	decDataPtr->markG04 = false;
	decDataPtr->markX = false;
	decDataPtr->markY = false;
	decDataPtr->markF = false;
	decDataPtr->markG06 = false;
	decDataPtr->markG07 = false;

	decDataPtr->lineCmdValid = false;
	decDataPtr->lineNumberValid = false;
	decDataPtr->dwellValid = false;

		
	decDataPtr->decState = DEC_IDLE;  // next decoder state


   return 1;
} //decInit() 


//***********************************************************
//
//***********************************************************
int decIdle(DEC_DATA  *decDataPtr)
{  // nc file available??? yes, change to open file state
	
	
	if(cncDataPtr->linkData.linkToDecData.linkToDecDataValid == true)
	{
		if(cncDataPtr->linkData.linkToDecData.ncFileValid == true
            && cncDataPtr->linkData.linkToDecData.START == true)
		{
			cncDataPtr->linkData.linkToDecData.START = false;

			decDataPtr->decState = DEC_OPEN_FILE;
		}
		cncDataPtr->linkData.linkToDecDataValid = false;
	}
   return 1;
} //decIdle() 

//***********************************************************
//
//***********************************************************
int decOpenFile(DEC_DATA  *decDataPtr)
{  
	
	if(cncDataPtr->linkData.linkToDecData.ncFileValid == true)
	{
		strcpy(decDataPtr->ncFileName , cncDataPtr->linkData.linkToDecData.ncFileName);
		decDataPtr->ncFilePtr = fopen(decDataPtr->ncFileName , "r");

		if(decDataPtr->ncFilePtr == NULL)
		{
			// DEC_ERROR;
			decDataPtr->decState = DEC_ERROR;
			return -1;
		}
		/*else
		{
			decDataPtr->fileOpen = true;
			decDataPtr->decState = DEC_PRE;
		}*/
	}
	
	
	//***********************************************************
	//
	//************************************************************
	
	int  result=0;
	int  size;
	
	// open file and preprocessing

	//decDataPtr->ncFilePtr= fopen("fortest.txt", "r");//"r" read, "w" write
	//check if open file is successful!
	if(decDataPtr->ncFilePtr !=NULL)
	{
		
		//preprocessing
		result = fseek(decDataPtr->ncFilePtr, 0, SEEK_END);
		size = ftell(decDataPtr->ncFilePtr);
		result = fseek(decDataPtr->ncFilePtr, 0, SEEK_SET);

//		char *dynamicBufferReset[10000];
		//using dynamic buffer or memory to hold all file text!
		decDataPtr->dynamicBufferPtr = (char *)malloc(size+1);

		for(int i=0;i<size; i++)
		{
			decDataPtr->dynamicBufferPtr[i] = '\0';

		}



//		delByteSpace((char *)(decDataPtr->dynamicBufferPtr), sizeof(decDataPtr->ncFilePtr))
/*		
		
		
		
		
		for(int i=0 ; i<size ;i++)
		{
			dynamicBufferReset[i] = '\0'; 
			(decDataPtr->dynamicBufferPtr) = dynamicBufferReset[i];
		}
*/		

		if(decDataPtr->dynamicBufferPtr != NULL)
		{
			result = fread(decDataPtr->dynamicBufferPtr, sizeof(char),size,decDataPtr->ncFilePtr);
			//fread(decDataPtr->asciiPtr,sizeof(char),size,decDataPtr->ncFilePtr);
			decDataPtr->asciiPtr=decDataPtr->dynamicBufferPtr;
			decDataPtr->decState = DEC_LOOP;
		}
		else 
		{
			decDataPtr->decState=DEC_ERROR;
			return -1;
		}


	}

   return 1;
} //decOpenFile() 

//***********************************************************
//
//***********************************************************
int decLoop(DEC_DATA  *decDataPtr)
{ // decoding line by line
	bool  line = true;
	int   result = 0;
	int i = 0;
	while(line)
	{
		
		
		switch(decDataPtr->asciiPtr[i])//為什麼總是讀到'??'?
		{
		case 'N':
		case 'n':
			nfunction(decDataPtr);
			break;
		case 'G':
		case 'g':
			gfunction(decDataPtr);
			break;
		case 'X':
			result = xFunction(decDataPtr);
			break;
		case 'Y':
			result = yFunction(decDataPtr);
			break;
		case 'D':
		case 'd':
			dFunction(decDataPtr);
			break;
		case ' ':
			decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);
			break;
		case 'F':
		case 'f':
			 ffunction(decDataPtr);
			 break;
		case 'M':
		case 'm':
			decDataPtr->lineCmd = M30_PROG_END;
			decDataPtr->lineCmdValid = true;
			decDataPtr->asciiPtr++;
			decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);
			decDataPtr->asciiPtr = passDigit(decDataPtr->asciiPtr);
			break;
		case '/':
			decDataPtr->asciiPtr = passNote(decDataPtr->asciiPtr);
			break;
		case '\0':
			//endOfFile();
			return 1;
		case '\n':
		case ';':
			decDataPtr->asciiPtr = passStopSign(decDataPtr->asciiPtr);
			endOfLine(decDataPtr);   //pack data DEC_TO_INTP_DATA_BLOCK
			line = false;
			// exit DEC_LOOP, next state DEC_WRITE_OUT to write decoded data to INTP
			break;
		default:
			decDataPtr->decState=DEC_ERROR;
			line = false;
			// exit DEC_LOOP, next state DEC_WRITE_OUT to write decoded data to INTP
			break;
		}
		
	}
   return 1;
} //decLoop() 


//***********************************************************
//
//***********************************************************
int decError(DEC_DATA  *decDataPtr)
{ // decoding line by line

   return 1;
} //decLoop() 

//*******************************************************************************
//
//*******************************************************************************
int decWriteOut(DEC_DATA *decDataPtr)
{
	
	if(cncDataPtr->linkData.decToLinkBlockValid == false)
	{
		cncDataPtr->linkData.decToLinkBlock = decDataPtr->decToLinkBlock;
		cncDataPtr->linkData.decToLinkBlockValid = true;

		decAfterWrite(decDataPtr);

		decDataPtr->asciiPtr = passNote(decDataPtr->asciiPtr);

		if(cncDataPtr->linkData.decToLinkBlock.lineCmd == M30_PROG_END)
		{
			decWaitM30(decDataPtr);
		}
		else
		{
		   decDataPtr->decState = DEC_LOOP;		
		}

	}
	else
	{
		return -1;
	}

	return 1;
}

//*******************************************************************************
//
//*******************************************************************************
int decWaitM30(DEC_DATA *decDataPtr)
{
	//if M30 excuted in real time in INTP
	//free dyn memory <> malloc()
	//fclose file close file <> fopen()
	//clear/set line related data in DEC_DATA
	return 1;
}


