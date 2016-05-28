#include "stdafx.h"
#include "..\INC\utinity.h"
#include "..\..\DEC\INC\DEC.h"
#include <string.h>

/*#include "..\..\CNC\INC\cnc.h"  // include user defined header file

extern CNC_DATA* cncDataPtr;*/

//***********************************************************************
//
//***********************************************************************

int clearByteSpace (char *startPtr, int size)
{
	for(int i= 0; i<size; i++)
	{
		*startPtr=0;
		startPtr++;// pointer addition
		// ++ = +4 byte for pointer of int
	}

	return 1;
}

//int PassSpace();

char *passSpace(DEC_DATA *decdataPtr)
{
	while(decdataPtr->asciiPtr==(char*)' ')
	{
		decdataPtr->asciiPtr++;
	}

	return decdataPtr->asciiPtr;
}





//***************************************************************
//
//***************************************************************
/*
int passSpace(DEC_DATA *decDataPtr)
{
	while (*decDataPtr->asciiPtr==' ')
	{
		decDataPtr->asciiPtr++;  // pass all space
	}
   return 1;
} // passSpace()
*/


//***************************************************************
//
//***************************************************************
char  *passSpace(char *asciiPtr)
{
	while (*asciiPtr == ' ' || *asciiPtr == '	')
	{
		asciiPtr++;  // pass all space
	}

   return asciiPtr;
} // passSpace()



//***************************************************************
//
//***************************************************************
char  *passDigit(char *asciiPtr)
{
	while ( (*asciiPtr >= '0') &&  (*asciiPtr <= '9'))
	{
		asciiPtr++;  // pass digit
	}

   return asciiPtr;
} // passDigit()

//***************************************************************
//
//***************************************************************

char   *passFloat(char *asciiPtr)
{
	
		if(*asciiPtr == '+' || *asciiPtr == '-')
		{
			asciiPtr++;
			
			asciiPtr = passDigit(asciiPtr);
			

			if(*asciiPtr == '.')
			{
				asciiPtr ++;
				asciiPtr = passDigit(asciiPtr);
			}
		}
		else if((*asciiPtr >= '0') &&  (*asciiPtr <= '9'))
		{
			asciiPtr = passDigit(asciiPtr);
			if(*asciiPtr == '.')
			{
				asciiPtr ++;
				asciiPtr = passDigit(asciiPtr);
			}
		}
		else
		{
			return asciiPtr;

		}

		return asciiPtr;

}

//****************************************************************************
//
//****************************************************************************

char   *passNote(char *asciiPtr)
{
	if(*asciiPtr == '/')
	{
		while(*asciiPtr != '\n')
		{
			asciiPtr++;
		}

	}

	asciiPtr ++;

	return asciiPtr;

}

//********************************************************
//
//********************************************************

char   *passStopSign(char *asciiPtr)
{
	if(*asciiPtr == ';')
	{
		asciiPtr ++ ;
		asciiPtr = passSpace(asciiPtr);
	}


	return asciiPtr;
}
