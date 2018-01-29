#ifndef _WIN32_WINNT
#define _WIN32_WINNT 1537
#endif

#include <windows.h>
#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#define _WIN32_WINNT 1537
#endif
#include <WinCon.h>
#include <iostream>
//#include <fstream>
//#include <stdio.h>
//#include <stdlib.h>
#include <conio.h> 

using namespace std;

#include "myconsole.h"


//this function outputs a string str at position (x,y) of the screen 
void OutputString(int x,int y,char *str)
{    
    COORD c;
    c.X = x;
    c.Y = y;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h,c);
    cout << str;
    cout.flush();
}

//this function will clear the screen
void ClearScreen()
{
	CONSOLE_SCREEN_BUFFER_INFO info;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(h,&info);
	system("cls");
	SetConsoleCursorPosition(h,info.dwCursorPosition);
	
}

//alternative to ClearScreen for Windows7 platform
/*void ClearScreen1()
{
	PlaceCursor(0,0);

	cout << string(10000, ' ');

	cout.flush();
	PlaceCursor(0,0);
}
*/
//this function will place the cursor at a certain position on the screen
void PlaceCursor(int x,int y)
{
    COORD c;
    c.X = x;
    c.Y = y;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(h,c);
}




//this function checks if a key is pressed and if a key is pressed
//then it returns the ascii code/virtual code of the key pressed
//specialKey would be returned as true if it is a key associated with a non-printable character
//specialKey would be returned as false if ordinary printable characters are typed
//if no key is pressed then specialKey value will not be changed
//the parameter waitTime specifies how long we have to wait for an input
//the default value is 20 millisecond.  If within the wait time no key is pressed
//the function returns zero.
unsigned int CheckWhichKeyPressed(bool &specialKey,int waitTime)
{
	HANDLE h= GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD r;
	DWORD w = 1;
	DWORD eventss;
	DWORD waitResult=0;
	int keypressed = false;
	int toReturn = 0;

	waitResult = WaitForSingleObject(h,waitTime);

	if (waitResult == WAIT_OBJECT_0)
	{
		//FlushConsoleInputBuffer(h);..commented out as this takes to asynchronous mode on some systems
		keypressed = ReadConsoleInput(h,&r,1,&eventss);
		
		if (keypressed && r.EventType==KEY_EVENT && r.Event.KeyEvent.bKeyDown)
		{	
			toReturn = r.Event.KeyEvent.wVirtualKeyCode;

			if (r.Event.KeyEvent.uChar.AsciiChar)
			{
				toReturn = r.Event.KeyEvent.uChar.AsciiChar;
				specialKey = false;
			}
			else
				specialKey = true;

		}
		//this should make sure that checkKeyPressed is not called twice for arrow keys
		if (toReturn == 224)
			toReturn = CheckWhichKeyPressed(specialKey,waitTime);

		
		FlushConsoleInputBuffer(h);
	}
	return toReturn;
}




void GetMaxWindowSize(int &maxHorizontal,int &maxVertical)
{
    COORD c;
//    c.X = x;
 //   c.Y = y;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
	c = GetLargestConsoleWindowSize(h);
	maxHorizontal = c.X;
	maxVertical = c.Y;
}

//set the title of the window
void SetWindowTitle(char Title[])
{
  //  SetConsoleTitle();
}


void GetMaxWindowCoordinates(int &x,int &y)
{
    CONSOLE_SCREEN_BUFFER_INFO info;

    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    GetConsoleScreenBufferInfo(h,&info);
    x = info.srWindow.Right;
    y = info.srWindow.Bottom;
}

//won't set for more than a certain height and certain width, depending
//upon your system
void SetWindowSize(int width,int height)
{
    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    bool bAbs = true;
    SMALL_RECT r;

    r.Left = 0;
    r.Top  = 0;
    r.Right = width;
    r.Bottom = height;

    SetConsoleWindowInfo(h,bAbs,&r);
}

//changes the color of a certain co-ordinate
//color can be BACKGROUND_GREEN, BACKGROUND_BLUE,BACKGROUND_RED or a combination of these using | operator
bool SetColorAtPoint(int x,int y,int color)
{
    COORD c,size;
    c.X = x;
    c.Y = y;
    size.X = 1;
    size.Y = 1;


    HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);
    
    WORD w = color;
    unsigned long written = 0;

    WriteConsoleOutputAttribute(h,&w,1,c,&written);

    if (written)
        return true;

    return false;
}


//draw a line
void myLine(int x1, int y1, int x2, int y2,int color)
{
	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    //change the color by changing the values in RGB (from 0-255)
	HPEN pen =CreatePen(PS_SOLID,2,RGB(color,color+1,color+2)); //2 is the width of the pen
    SelectObject(device_context,pen);
	MoveToEx(device_context,x1,y1,NULL);
    LineTo(device_context,x2, y2);
	ReleaseDC(console_handle, device_context);  
}

//draw a rectangel
void myRectangle(int x1, int y1, int x2, int y2,int color)
{
	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    //change the color by changing the values in RGB (from 0-255)
    HPEN pen =CreatePen(PS_SOLID,2,RGB(color,color,color)); 
    SelectObject(device_context,pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(0,0,0));
	SelectObject(device_context,brush);
	
	Rectangle(device_context,x1,y1,x2,y2);
	ReleaseDC(console_handle, device_context); 
}

//draw an ellipse
void myEllipse(int x1, int y1, int x2, int y2,int color)
{
	HWND console_handle = GetConsoleWindow();
    HDC device_context = GetDC(console_handle);

    //change the color by changing the values in RGB (from 0-255)
    HPEN pen =CreatePen(PS_SOLID,2,RGB(color,color,color)); 
    SelectObject(device_context,pen);
	HBRUSH brush = ::CreateSolidBrush(RGB(0,0,0));
	SelectObject(device_context,brush);
	Ellipse(device_context,x1,y1,x2,y2);
	ReleaseDC(console_handle, device_context);

}
