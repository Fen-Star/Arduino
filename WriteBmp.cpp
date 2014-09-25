/*
(c) Wesley Rogers fenstar.co 2014
Revision 0.1.0
Future Use: http://code.fenstar.co/psudo-c/arduino.html?lib=WriteBmp
https://github.com/Fen-Star/Arduino/blob/master/WriteBmp.cpp

*/

const int ABORT = 3;				//
const int ERROR = 2;				//Warning codes, see
const int WARNING = 1;				//help for meanings.
const int SUCESS = 0;				//

struct display //Need to change struct name
{
	int rows;
	int cols;
	char[] bmp;
	int LastWrite;
	int FrameSkip;
}

//struct display returned
GetPFrame()
{

}

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

#ifdef _FRAMECHECK
int frameTime(int maxtime, int opNumber, int opTime)
{
	/*
	if (endtime + timetorunerrorcheck) < maxtime
	return SUCESS;
	if (ERRLOG)
	errorlog("error");
	return ABORT;
	*/
}
#endif




