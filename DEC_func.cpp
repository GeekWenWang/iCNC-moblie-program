#include "stdafx.h"
#include <stdio.h>
#include <stdlib.h>

#include "..\INC\Dec.h"
#include "..\..\CNC\INC\cnc.h"
#include "..\..\UTINITY\INC\utinity.h"
#include "..\..\LINK\IRC\link.h"





 /*  void clearByteSpace(char *startPtr, int size)
{
   int    i;

   for (i = 0; i < size; i++ )
   {
     *startPtr = 0;
	  startPtr++;  // next byte
   }
   return;
} // claerByteSpace()*/

//*******************************************************
//
//*******************************************************
/*
int delByteSpace((char *)dynamicBufferPtr, sizeof(ncFilePtr))
{
   int       *intPtr;  // intPtr++ -> add 4 bytes
   char      *bytePtr;
   int       n;

   bytePtr = (char *)dynamicBufferPtr;     // code for delete byte space
   bytePtr = (char *)ncFilePtr;

   n = sizeof(ncFilePtr);  // in byte
   for (int i = 0; i < n; i++ )
   {
     *bytePtr = 0;
	 bytePtr++;  // next byte
   }
  
   return 1;

}
*/

//*******************************************************
//n function
//*******************************************************
int nfunction(DEC_DATA *decDataPtr)
{
	if(decDataPtr->markN==true)
	{
		decDataPtr->decState=DEC_ERROR;
		return -1;
	}
	else
	{
		decDataPtr->ncLine[0] = 'N';
		decDataPtr->asciiPtr++;
		decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);

		//check N format N[digit]
		//if(isDigit() )
		//{//no digit error!
		//
		//return -1;
		//}
		decDataPtr->Ncommand = atoi(decDataPtr->asciiPtr);//Ncommand的字元長度?
		

		decDataPtr->markN = true;
		decDataPtr->asciiPtr = passDigit(decDataPtr->asciiPtr);
	    decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);
	}
	return 1;
}

//*******************************************************
//g function
//*******************************************************
int gfunction(DEC_DATA *decDataPtr)
{
	if(decDataPtr->markG00==true && decDataPtr->markG90==true)
	{
		decDataPtr->decState=DEC_ERROR;
		return -1;
	}	
	else
	{
		decDataPtr->asciiPtr ++;

		int gCommand = atoi(decDataPtr->asciiPtr);

		switch(gCommand)
		{
			case 0:
			decDataPtr->lineCmd = G00_CMD;
			decDataPtr->markG00 = true;
			decDataPtr->lineCmdValid = true;
			break;

			case 4:
			decDataPtr->lineCmd = G04_DWELL_TIME;
			decDataPtr->markG04 = true;
			decDataPtr->lineCmdValid = true;
			decDataPtr->asciiPtr = passDigit(decDataPtr->asciiPtr);
			decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);
			decDataPtr->dwellTime = atoi(decDataPtr->asciiPtr);
			decDataPtr->asciiPtr = passDigit(decDataPtr->asciiPtr);
			break;

			case 6:
			decDataPtr->lineCmd = G06_ROT_CW;
			decDataPtr->markG06 = true;
			decDataPtr->direction = true;
			decDataPtr->lineCmdValid = true;
			break;

			case 7:
			decDataPtr->lineCmd = G07_ROT_CCW;
			decDataPtr->markG07 = true;
			decDataPtr->direction = false;
			decDataPtr->lineCmdValid = true;
			break;

		}
	
		if(decDataPtr->relValid == false)
		{
			if(atoi(decDataPtr->asciiPtr)==90)
			{
				decDataPtr->relAbs = false;		
				decDataPtr->relValid = true;
			}
			else if(atoi(decDataPtr->asciiPtr)==91)
			{
				decDataPtr->relAbs = true;		
				decDataPtr->relValid = true;
			}
		}
		
		decDataPtr->asciiPtr =passDigit(decDataPtr->asciiPtr);
	    decDataPtr->asciiPtr =passSpace(decDataPtr->asciiPtr);
	}

	return 1;
}
//*******************************************************
//x function
//*******************************************************
int xFunction(DEC_DATA *decDataPtr)
{
	if(decDataPtr->markX == true )
	{
		decDataPtr->decState=DEC_ERROR;
		return -1;
	}
	else
	{
		decDataPtr->asciiPtr++;
		decDataPtr->asciiPtr =passSpace(decDataPtr->asciiPtr);
		//check if xyCoordinate is float

		decDataPtr->startPos.xyCoordinate[0]=atoi(decDataPtr->asciiPtr);
		decDataPtr->markX = true;
		decDataPtr->asciiPtr = passFloat(decDataPtr->asciiPtr);
	    decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);
	}


	return 1;
}

//*******************************************************
//y function
//*******************************************************
int yFunction(DEC_DATA *decDataPtr)
{
	if(decDataPtr->markY == true )
	{
		decDataPtr->decState=DEC_ERROR;
		return -1;
	}
	else
	{
		decDataPtr->asciiPtr++;
		 decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);
		decDataPtr->startPos.xyCoordinate[1]=atoi(decDataPtr->asciiPtr);
		decDataPtr->markY = true;
		decDataPtr->asciiPtr = passFloat(decDataPtr->asciiPtr);
	    decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);
	}
	return 1;
}

//*******************************************************************************
//
//*******************************************************************************
int dFunction(DEC_DATA *decDataPtr)
{
	decDataPtr->asciiPtr++;
	
	
	decDataPtr->angleVaild = true;
	
	decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);
	decDataPtr->angle = atof(decDataPtr->asciiPtr);
	
	decDataPtr->asciiPtr = passFloat(decDataPtr->asciiPtr);
	
	decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);

	return 1;
}

//*******************************************************************************
//
//*******************************************************************************
int ffunction(DEC_DATA *decDataPtr)
{
		if(decDataPtr->markF==true)
	{
		decDataPtr->decState=DEC_ERROR;
		return -1;
	}
	else
	{
		decDataPtr->asciiPtr++;
		

		//check N format N[digit]
		//if(isDigit() )
		//{//no digit error!
		//
		//return -1;
		//}
		//Ncommand的字元長度?
		

		decDataPtr->markF = true;
		
		decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);
		decDataPtr->speed = atof(decDataPtr->asciiPtr);
		
		decDataPtr->asciiPtr = passFloat(decDataPtr->asciiPtr);

		decDataPtr->asciiPtr = passSpace(decDataPtr->asciiPtr);
	    
	}
	
	return 1;
}

//*******************************************************************************
//
//*******************************************************************************
int endOfLine(DEC_DATA *decDataPtr)
{
	//delByteSpace(&decDataPtr->decToLinkBlock, sizeof(DEC_TO_LINK_BLOCK));

		
	if(decDataPtr->markN == true )
		{
			decDataPtr->decToLinkBlock.Ncommand = decDataPtr->Ncommand;
			decDataPtr->decToLinkBlock.lineNumberValid = decDataPtr->markN;
			decDataPtr->markN = false;
		}

	if(decDataPtr->markF == true )
	{
		decDataPtr->decToLinkBlock.speed = decDataPtr->speed;
		decDataPtr->decToLinkBlock.speedValid = decDataPtr->markF ;
		decDataPtr->markF = false;
	}
	
	
	if(decDataPtr->lineCmdValid == true && decDataPtr->lineCmd !=NULL_CMD)
	{
		switch(decDataPtr->lineCmd)
		{
		case G00_CMD:
		
			if(decDataPtr->markG00==true)
			{
				decDataPtr->decToLinkBlock.lineCmdValid = decDataPtr->lineCmdValid;
				decDataPtr->decToLinkBlock.lineCmd = decDataPtr->lineCmd;
				decDataPtr->lineCmdValid = false;
				decDataPtr->markG00 = false;
				decDataPtr->lineCmd =NULL_CMD;//初始化於writeout
			}	
			if(decDataPtr->relValid == true)
			{
				decDataPtr->decToLinkBlock.relValid = decDataPtr->relValid ;
				decDataPtr->decToLinkBlock.relAbs = decDataPtr->relAbs;
				decDataPtr->relValid = false;
			}
		
			else
			{
			   return -1;
			}
			if(decDataPtr->markX==true || decDataPtr->markY==true)
			{
			for(int i=0; i<2; i++)
			{
				if(decDataPtr->markX==true || decDataPtr->markY==true)
				{
					decDataPtr->decToLinkBlock.xyCoordinate[i] = decDataPtr->startPos.xyCoordinate[i];//if X orY doesn't have number we have 0; 不可Init
					decDataPtr->decToLinkBlock.xyValid[i] = true;
					decDataPtr->markX = false;
				}
			}
			decDataPtr->markY = false;
			}
			else
			{
				return -1;
			}
			break;


		case G04_DWELL_TIME:
			if(decDataPtr->markG04 == true )
			{
				decDataPtr->dwellValid = decDataPtr->markG04;
				decDataPtr->decToLinkBlock.dwellValid = decDataPtr->dwellValid;
				decDataPtr->decToLinkBlock.lineCmd = decDataPtr->lineCmd;
				decDataPtr->decToLinkBlock.lineCmdValid = decDataPtr->lineCmdValid;
				decDataPtr->decToLinkBlock.dwellTime = decDataPtr->dwellTime;
				decDataPtr->lineCmdValid = false;
				
				decDataPtr->dwellValid = false;

				decDataPtr->markG04 =false;

				decDataPtr->lineCmd =NULL_CMD;
			}
			
			else
			{
			   return -1;
			}
			break;
		case G06_ROT_CW:
			if(decDataPtr->markG06 == true)
			{
				decDataPtr->decToLinkBlock.lineCmd = decDataPtr->lineCmd;
				decDataPtr->decToLinkBlock.lineCmdValid = decDataPtr->lineCmdValid;
				decDataPtr->decToLinkBlock.angle = decDataPtr-> angle;
				decDataPtr->decToLinkBlock.angleValid = decDataPtr->markG06;
				
				decDataPtr->lineCmdValid = false;
				decDataPtr->markG06 = false;

				decDataPtr->decToLinkBlock.direction = decDataPtr->direction;

				decDataPtr->lineCmd =NULL_CMD;
			}
			else
			{
				return -1;
			}
			break;
		case G07_ROT_CCW:
			if(decDataPtr->markG07 == true)
			{
				decDataPtr->decToLinkBlock.lineCmd = decDataPtr->lineCmd;
				decDataPtr->decToLinkBlock.lineCmdValid = decDataPtr->lineCmdValid;
				decDataPtr->decToLinkBlock.angle = decDataPtr-> angle;
				decDataPtr->decToLinkBlock.angleValid = decDataPtr->markG07;
				
				decDataPtr->lineCmdValid = false;
				decDataPtr->markG07 = false;

				decDataPtr->decToLinkBlock.direction = decDataPtr->direction;

				decDataPtr->lineCmd =NULL_CMD;
			}
			else
			{
				return -1;
			}
			break;
		case M30_PROG_END:
			if(decDataPtr->lineCmdValid == true)
			{
				decDataPtr->decToLinkBlock.lineCmd = decDataPtr->lineCmd;
				decDataPtr->decToLinkBlock.lineCmdValid = decDataPtr->lineCmdValid;
				decDataPtr->lineCmdValid = false;
				decDataPtr->lineCmd =NULL_CMD;
			}
			break;
	
		default:
			return -1;
			break;
		}
	}

	decDataPtr->decState = DEC_WRITE_OUT;
	return 1;
}


//*******************************************************************************
//
//*******************************************************************************
int decAfterWrite(DEC_DATA *decDataPtr)
{
	//clear/set line related data in DEC_DATA
	//modal or one shot command???
	//modal: effective once set
	//one shot: effective only in one line
	//
	if(decDataPtr->decToLinkBlock.lineNumberValid == true)
	{
		decDataPtr->Ncommand = 0;
	}

	if(decDataPtr->decToLinkBlock.speedValid == true)
	{
		decDataPtr->speed = 0.0;
	}

	if(decDataPtr->decToLinkBlock.relValid == true)
	{
		decDataPtr->relAbs = false;
	}

	if(decDataPtr->decToLinkBlock.dwellValid ==true)
	{
		decDataPtr->dwellTime = 0.0;
	}

	/*if(decDataPtr->decToLinkBlock.angleValid == true)
	{
		decDataPtr-> angle = 0.0;
		decDataPtr->direction  = false;
	}*/

	return 1;
}

//*************************************************
//
//*************************************************

/*void endOfFile(void)
{


}*/