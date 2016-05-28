#ifndef _LINK_H_
#define _LINK_H_

enum LINE_CMD{G00_CMD,G04_DWELL_TIME,G06_ROT_CW,G07_ROT_CCW,M30_PROG_END,NULL_CMD};



struct DEC_TO_LINK_BLOCK
{
	LINE_CMD       lineCmd;
	int Ncommand;
	bool lineCmdValid;
	bool lineNumberValid;
	int G_command[2];
	bool xyValid[2]; 
	double  xyCoordinate[2];

	double speed;
	bool speedValid;
	double dwellTime;
	bool dwellValid;

	bool            relAbs;              // false G90: abs,  true G91: rel
	bool			relValid;
	double          angle;
	bool            direction;           // true: CW, false: CCW
	bool			angleValid;
	bool			decToLinkDataValid;       
};


struct MMI_TO_LINK_DATA
{
	char ncFileName[200];
	bool ncFileValid;
	bool mmiToLinkDataValid;

	bool START;
	bool RESET;

};

struct LINK_TO_DEC_DATA
{
	char ncFileName[200];
	bool ncFileValid;
	bool linkToDecDataValid;

	bool START;
	bool RESET;

};

struct LINK_TO_MMI_DATA
{
	int     counter;
	double	CarCoordinate[3];
	char	serialCmd[4];
	bool	serialCmdVaild;
	bool    linkToMmiDataValid;

};

struct INTP_TO_LINK_DATA
{
	double	CarCoordinate[3];
	char	serialCmd[4];
	bool	serialCmdVaild;
	bool    intpToLinkDataValid;

	bool    RESET;
};

struct LINK_TO_INTP_DATA
{
	bool			cmdValid;
	// full info of one NC line
	int             lineNumber; // N code
	bool			lineNumberVaild;
	LINE_CMD	    lineCmd;   // ensure that only one effective command!!
	bool			lineCmdVaild;
	bool            relAbs;    // false G90: abs,  true G91: rel
	bool			relValid;
	double          xyCoordinate[2];    // xy[0], xy[1]
	bool            xyValid[2]; // reset at line begin
	double          angle;
	bool            direction;  // true: CW, false: CCW
	bool			angleValid;
	double speed;// F
	double			dwellTime; 
	bool            dwellValid;
	bool            speedValid;
	bool			linkToIntpDataValid;
};


struct LINK_DATA
{
	DEC_TO_LINK_BLOCK decToLinkBlock;
	bool decToLinkBlockValid;

	LINK_TO_INTP_DATA linkToIntpData;
	bool linkToIntpDataValid;
	
	INTP_TO_LINK_DATA intpToLinkData;

	MMI_TO_LINK_DATA mmiToLinkData;
	bool mmiToDecDataValid;

	LINK_TO_DEC_DATA linkToDecData;
	bool linkToDecDataValid;

	LINK_TO_MMI_DATA linkToMmiData;
	bool linkToMmiDataValid;

	
	
};


int linkInit(LINK_DATA* linkDataPtr);

int mmiToLinkDataInit(LINK_DATA* linkDataPtr);
int linkToMmiDataInit(LINK_DATA* linkDataPtr);
int decToLinkDataInit(LINK_DATA* linkDataPtr);
int linkToDecDataInit(LINK_DATA* linkDataPtr);
int intpToLinkDataInit(LINK_DATA* linkDataPtr);
int linkToIntpDataInit(LINK_DATA* linkDataPtr);

int linkMain(LINK_DATA* linkDataPtr);







#endif