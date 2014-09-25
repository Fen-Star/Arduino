/*
(c) Wesley Rogers fenstar.co 2014
Revision 0.1.0
http://code.fenstar.co/psudo-c/arduino.html?function=minihex
github
*/

/*
.h file info (to be moved)

*/

/*
struct display
{
	int rows;
	int cols;
	char[] bmp;
}
*/

//Defined constants
const int WIDTH_PX = 4;				//Width of chars in px
const int HEIGHT_PX = 6;			//Height of
const int SNAP_PX = 2;				//
const int OVERSNAP_PX = 8;			//Height of default grid
const int ABORT = 3;				//
const int ERROR = 2;				//
const int WARNING = 1;				//
const int SUCESS = 0;				//
const int HEXCHARS = 16;			//Number of chars in the hex set
const int ROLL_OVER = 2;			//
const int ROLL_OFSET = 1;			//

//Derived constants
const int ROLL_SKIP = OVERSNAP_PX / SNAP_PX - ROLL_OVER;


int MiniHex(char[] hexString, int row, int col, display disp )
{
	//Prepwork
	//check for errors
	if( !(row%SNAP_PX) || (row  >= disp.rows) || (col >= disp.cols))
	{
		if (ERRLOG)
			errorLog("MiniHex line xx ERROR: Invalid starting location. Minihex exited without action.");
		return ABORT;				//Don't even try to figure out what they wanted.
	}
	if( ((col + sizeOf(hexString) * WIDTH_PX) >= disp.cils) || ((row + HEIGHT_PX) >= disp.rows))
	{
		warningState = WARNING; 	//Hope they know what they are doing
		if (ERRLOG)
			errorLog("MiniHex line xx WARNING: String may attemp to write off screen.");
		if (SAFEMODE)
		{
			if (ERRLOG)
				errorLog("MiniHex line xx SAFEMODE: Enabled. Minihex exited without action.");
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
	warningState = WriteLineHex(hexString, chRow, col, ofRow, warningState);
	if(warningState == ABORT)
	{
		if (ERRLOG)
			errorLog("MiniHex line xx ERROR: WriteLineHex aborted the operation, miniHex will now abort as well");
		return ERROR;
	}
	chRow++;
	if (ofRow > ROLL_OVER)
	{
		ofRow = ofRow + ROLL_SKIP;
		warningState = WriteLineHex(hexString, chRow, col, ofRow, warningState);
	}
	return warningState;
}
