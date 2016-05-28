#ifndef _CNC_H
#define _CNC_H

#include "..\..\DEC\INC\dec.h"
#include "..\..\MMI\INC\mmi.h"
#include "..\..\INTP\INC\intp.h"
#include "..\..\LINK\IRC\link.h"

struct CNC_DATA
{
   DEC_DATA           decData;
   INTP_DATA          intpData;
   MMI_DATA           mmiData;
   LINK_DATA          linkData;

};

int nrtMain(CNC_DATA *cncDataPtr);
int rtMain(CNC_DATA *cncDataPtr);
int cncInit(void);
int cncMain(CNC_DATA *cncDataPtr);

#endif