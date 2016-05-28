#ifndef _DEC_H
#define _DEC_H
#include <stdio.h>
#include <stdlib.h>

#include "..\..\MMI\INC\MMI.h"
#include "..\..\LINK\IRC\link.h"

#define CHAR_IN_LINE_MAX 200

enum DEC_STATE { DEC_INIT, DEC_IDLE, DEC_OPEN_FILE, DEC_LOOP, DEC_ERROR, DEC_WRITE_OUT, DEC_WAIT_M30 };




struct POINT
{
	double     xyCoordinate[2];
};  //POINT

struct DEC_DATA // decoder data
{  


	FILE    *ncFilePtr;
	DEC_STATE decState;
	// member
	int      lineNumber;
	bool	lineNumberValid;
	//char     ncLine[80];
	char     ncLine[CHAR_IN_LINE_MAX];  // new line from NC file
	char     *asciiPtr;    // pointer
	char     *dynamicBufferPtr;
	
	POINT    startPos;
	
	mmiToDecData *mmiToDecDataPtr;

	LINE_CMD  lineCmd;
	bool lineCmdValid;

	int Ncommand;
	bool markN;
	
	char ncFileName[200];

	double dwellTime;
	bool dwellValid;

	bool markG00;
	bool markG90;
	bool markG04;
	bool markG06;
	bool markG07;


	bool            relAbs;    // false G90: abs,  true G91: rel
	bool			relValid;

	int G_command[2];

	bool markX;

	bool markY;

	double speed;
	bool markF;

	double          angle;
	bool            direction;           // true: CW, false: CCW
	bool			angleVaild;
	bool			decToLinkDataValid;   

	DEC_TO_LINK_BLOCK  decToLinkBlock;
	
};  // DEC_DATA


//int delByteSpace((char *)decDataPtr, sizeof(DEC_DATA));

// functions in the same cpp file
int decInit(DEC_DATA  *decDataPtr); // function prototype
int decIdle(DEC_DATA  *decDataPtr);
int decOpenFile(DEC_DATA  *decDataPtr);
int decLoop(DEC_DATA  *decDataPtr);
int decMain(DEC_DATA  *decDataPtr);
int clearByteSpace(char *startPtr, int size);
int decWriteOut(DEC_DATA *decDataPtr);
int decAfterWrite(DEC_DATA *decDataPtr);
int decError(DEC_DATA  *decDataPtr);
int decWaitM30(DEC_DATA *decDataPtr);
int endOfLine(DEC_DATA *decDataPtr);

//decording function
int ffunction(DEC_DATA *decDataPtr);
int nfunction(DEC_DATA *decdataPtr);
int gfunction(DEC_DATA *decDataPtr);
int xFunction(DEC_DATA *decDataPtr);
int yFunction(DEC_DATA *decDataPtr);
int dFunction(DEC_DATA *decDataPtr);

//int delByteSpace((char *)dynamicBufferPtr, sizeof(ncFilePtr));

//int delByteSpace((char *)decDataPtr, sizeof(DEC_DATA));

#endif