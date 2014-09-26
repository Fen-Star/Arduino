/*
(c) Wesley Rogers fenstar.co 2014
Revision 0.1.1
Future Use: http://code.fenstar.co/psudo-c/arduino.html?lib=WriteBmp
https://github.com/Fen-Star/Arduino/blob/master/WriteBmp.cpp

*/

/*
This library is for writing 1 bit images in blocks of 1px width and 8px height. These are refered to as chars because the are the same size (1 byte) as a char and are stored in char arrys.

For example, the text image reading 'FOL'
	 ____________
	|			 |
	|			 |
	| ### ### #  |
	| #   # # #  |
	| ##  # # #  |
	| #   # # #  |
	| #   ### ## |
	|____________|
	
	Is translated into a binary image
	
	000000000000
	000000000000
	011101110100
	010001010100
	011001010100
	010001010100
	010001110110
	000000000000

	and each colum is stored in an 8 bit char
	
	0000 0000	00
	0111 1100	7C
	0001 0100	14
	0000 0100	04
	0000 0000	00
	0111 1100	7C
	0100 0100	44
	0111 1100	7C
	0000 0000	00
	0111 1100	7C
	0100 0000	40
	0000 0000	00
	
	Which is then put into an arrat of chars
	
	BumpSting FOL;
	FOL.bmp = [00,7C,14,04,00,7C,44,7C,00,7C,40,00]
	Now, the BumpSting is indexed to be usefull
	FOL.elements = 3;
	FOL.index = [1,5,9];
	FOL.width = [3,3,2];
	FOL.height = [1,1,1];
	
	As such, if you wish to return the 'F' from the string, and you know F is the first element you may simply use 
	first char = FOL.index[1]
	Width in chars =FOL.width[1]
	
	or the functiom
	PullBmpString(FOL,1);
	
	and retrive the relevent chars [7C,14,04]
*/
const int ABORT = 3;				//
const int ERROR = 2;				//Warning codes, see
const int WARNING = 1;				//help for meanings.
const int SUCESS = 0;				//

struct display 						//Need to change struct name
{
	int rows;						//
	int cols;						//
	char[] bmp;						//
	int LastWrite;					//
	int FrameSkip;					//
}

struct BumpString 					//Allows 
{
	char[] image;					//Binary data of the image(s)
	int elements;					//Number of images
	int[] index;					//Index for the first char of the corosponding image
	int[] width;					//With of image in chars (px)
	int[] height;					//Height of image ins chars (pix/8)
	#ifdef _HRINDEX
	std::string[] name;				//Human readable index names
	#endif
}

char[] PullBumpString(BumpString img, int pull)
{
	int i = o;
	int dex = img.index[pull];
	int stop = img.width[pull];
	char[img.width[pull]] output;
	for (i < stop)
	{
		output[i] = img.image[i+dex];
		i++;
	}
	return output;
}

#ifdef HRINDEX
char[] PullBumpString(BumpString img, std:string pull)
{

}
#endif
//struct display returned
GetPFrame()
{

}

int InvertFrame()
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




