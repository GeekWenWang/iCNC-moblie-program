#ifndef _UTINITY_H
#define _UTINITY_H

#include "..\..\DEC\INC\Dec.h"


int clearByteSpace (char *startPtr, int size);
//int passSpace(DEC_DATA *decDataPtr);
char  *passSpace(char *asciiPtr);
char  *passDigit(char *asciiPtr);
/*int delByteSpace((char *)cncDataPtr, sizeof(CNC_DATA));*/
char   *passFloat(char *asciiPtr);
char   *passNote(char *asciiPtr);
char   *passStopSign(char *asciiPtr);

#endif
