#ifndef _INTP_H_
#define _INTP_H_

#include "..\..\LINK\IRC\link.h"


enum INTP_STATE {INTP_NULL,INTP_INIT,INTP_IDLE,INTP_PRE,INTP_DWELL_TIME,INTP_EXE,INTP_CLOSE,INTP_ERROR };


struct INTP_DATA
{
	//input
	INTP_STATE      intpState;
	bool            cmdValid;
	int             lineNumber; // N code
	bool			lineNumberVaild;
	LINE_CMD	    lineCmd;   // ensure that only one effective command!!
	bool			lineCmdVaild;
	bool            relAbs;    // false G90: abs,  true G91: rel
	bool			relValid;
	double          xyCoordinate[2];    // xy[0], xy[1]
	bool            xyValid[2]; // reset at line begin
	bool            xyDirection;
	double          angle;
	double          absAngle;
	bool            direction;  // true: CW, false: CCW
	bool			angleValid;
	double          speed;      //F
	double			dwellTime; 
	bool            dwellValid;
	bool            speedValid;

	double          headPointer;
	
	LINK_TO_INTP_DATA    linkToIntpData;
	bool			linkToIntpDataValid;

	double          startPos[2];
	double          endPos[2];
	double          newPos[2];
	double          oldPos[2];//back up one point

	double          relPos[2];

	double          totalLength;
	double          sumLength; //new distance
	double          residualLength;//sumLength + residualLength = totalLength

	double          deltaLength;
	double          deltaAngle;
	double          angularVelocity;

	double          totalAngle;
	double          sumAngle; //new distance
	double          residualAngle;//sumAngle + residualAngle = totalAngle

	double          cyclingTime; //period of real-time timer

	int             counter;
	
	//北╰参阀阶
	//筿筿北瞶阶 笆北
	
	//output
	double	carCoordinate[3];
	char	serialCmd[2];
	bool	serialCmdValid;
	
	INTP_TO_LINK_DATA  intpToLinkData;
	bool    intpToLinkDataValid;

	bool    RESET;

};



int intpMain(INTP_DATA *intpDataPtr);
int intpInit(INTP_DATA *intpDataPtr);
int intpIdle(INTP_DATA *intpDataPtr);
int intpPre(INTP_DATA *intpDataPtr);
int intpExe(INTP_DATA *intpDataPtr);
int intpClose(INTP_DATA *intpDataPtr);
int intpError(INTP_DATA *intpDataPtr);

int countDownDwellTime(INTP_DATA *intpDataPtr);




#endif