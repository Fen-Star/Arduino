/*
(c) Wesley Rogers fenstar.co 2014
Revision 0.1.1
Future Use: http://code.fenstar.co/psudo-c/arduino.html?function=minihex
https://github.com/Fen-Star/Arduino/blob/master/MiniHex.cpp

*/

/*
.h file info (to be moved)
For modification of a single bit bmp by writing hex values.

Intent raiting (of 5 stars)
Speed:	***
Size:	***
Debug:	****

FRAMECHECK should not be defined unless you REALLY need it. It will usually take a lot longer to check and write to the error file than it will to just run the operation. If you have the time to run it then you won't need it.
*/

/*
struct display
{
	int rows;
	int cols;
	char[] bmp;
	int LastWrite;
	int FrameSkip;
}

*char[] MiniHexBmp;
*/

//Defined constants
const int WIDTH_PX = 4;				//Width of chars in px
const int HEIGHT_PX = 6;			//Height of
const int SNAP_PX = 2;				//explination goes here
const int OVERSNAP_PX = 8;			//Height of default grid !! THIS MUST BE 8 OR EVERYTHING WILL BURN !!
const int ABORT = 3;				//
const int ERROR = 2;				//Warning codes, see
const int WARNING = 1;				//help for meanings.
const int SUCESS = 0;				//
const int HEXCHARS = 16;			//Number of chars in the hex set
const int ROLL_OVER = 2;			//explination goes here
const int ROLL_OFSET = 1;			//explination goes here	!! Should be 1/2 ROLL_OVER rounded up !!

//Derived constants
const int ROLL_SKIP = OVERSNAP_PX / SNAP_PX - ROLL_OVER;


int MiniHex(char[] hexString, int row, int col, display disp )
{
	//Prepwork
	//check for errors
	if( !(row%SNAP_PX) || (row  >= disp.rows) || (col >= disp.cols))
	{
		if (ERRLOG)
			errorLog("MiniHex line xx ERROR: Invalid starting location. MiniHex exited without action.");
		return ABORT;				//Don't even try to figure out what they wanted.
	}
	if( ((col + sizeof(hexString) * WIDTH_PX) >= disp.cils) || ((row + HEIGHT_PX) >= disp.rows))
	{
		warningState = WARNING; 	//Hope they know what they are doing
		if (ERRLOG)
			errorLog("MiniHex line xx WARNING: String may attemp to write off screen.");
		if (SAFEMODE)
		{
			if (ERRLOG)
				errorLog("MiniHex line xx SAFEMODE: Enabled. MiniHex exited without action.");
			return ABORT;			//Guess they didn't know what they were doing
		}
	}
	//End (check for errors)
	int warningState = SUCESS;
	//Check for offset set
	int chRow = row/OVERSNAP_PX;
	int ofRow = (row%OVERSNAP_PX)/SNAP_PX;
	int ofRow = ofROW+ROLL_OFFSET;
	if (ofRow >= (ROLL_OVER +ROLL_SKIP)
		ofRow = ofRow - (ROLL_OVER +ROLL_SKIP);
	warningState = WriteLineMiniHex(hexString, chRow, col, ofRow, disp, warningState);
	if(warningState == ABORT)
	{
		if (ERRLOG)
			errorLog("MiniHex line xx ERROR: WriteLineHex aborted the operation, MiniHex will now abort as well");
		return ERROR;
	}
	chRow++;
	if (ofRow > ROLL_OVER)
	{
		ofRow = ofRow + ROLL_SKIP;
		warningState = WriteLineMiniHex(hexString, chRow, col, ofRow, disp, warningState);
	}
	if (ERRLOG==2)
		if (warningState==SUCESS)
			errorLog("MiniHex SUCESS");
	return warningState;
}

int WriteLineMiniHex(*char[] hexString, int chRow, int col, int ofRow, *display disp, int warningState)
{
	int i, j, hexVal, disp_bmp_char, hex_bmp_char;
	int hex_offset = 0; 				//what was I doing? It is past my bedtime.
	int disp_offset = ( chRow * disp.cols /*   * OVERSNAP_PX / 8   */ ) + row; //no point because OVERSNAP_PX has to be 8 anyway for this code to work without major modifications
	i = 0;
	disp_bmp_char = disp_offset;
	#ifdef _FRAMECHECK
	if(frameTime(disp.FrameSkip, sizeof(hexString), RUN)){
		if (ERRLOG)
			errorLog("WriteLineMiniHex line xx ERROR: WriteLineMiniHex aborted the operation because it will not finish before the next frame");
		return ERROR;
	}
	#endif
	for (i < sizeof(hexString))
	{
		if(hexString[i] <= 'f' && hexString[i] >= '0')
		{
			if(hexString[i] <= '9')
				hexVal = int (hexString[i] - '0');
			else if (hexString[i] >= 'a')
				hexVal = int (hexString[i] - 'a') + 10;
			else if (hexString[i] >= 'A' && hexString[i] <= 'F')
				hexVal = int (hexString[i] - 'A') + 10;
			else
			{
				if(ERRLOG)
					errorLog("WriteLineMiniHex ERROR: Invilid char in string. Aborting operation.");
				return ERROR;
			}
		}
		hex_offset = (HEXCHARS * ofRow + hexVal) * WIDTH_PX;
		j=0;
		for (j < WIDTH_PX)
		{
			WriteCharFromTo(MiniHexBmp, hex_bmp_char, disp.bmp, disp_bmp_char);
			hex_bmp_char++;
			disp_bmp_char++;
			j++;
		}
		i++;
	}
	
}

//I need to do pointers correctly, but I will fix that later WriteCharFromTo needs to go in another file anyway
int WriteCharFromTo(*char[] fromString, int fromIndex, *char[] toString, int toIndex)
{
	if(fromIndex >= sizeof(fromString))
	{
		if(ERRLOG)
			errorLog("WriteCharFromTo ERROR: Invilid Index. fromIndex is larger than fromString");
		return ABORT;
	}
	if(toIndex >= sizeof(toString))
	{
		if(ERRLOG)
			errorLog("WriteCharFromTo ERROR: Invilid Index. toIndex is larger than toString");
		return ABORT;
	}
	if(fromIndex < 0)
	{
		if(ERRLOG)
			errorLog("WriteCharFromTo ERROR: Invilid Index. fromIndex is less than zero.");
		return ABORT;
	}
	if(toIndex < 0)
	{
		if(ERRLOG)
			errorLog("WriteCharFromTo ERROR: Invilid Index. toIndex is less than zero.");
		return ABORT;
	}
	toString[toIndex]=fromString[fromIndex];
	return SUCESS;
}
