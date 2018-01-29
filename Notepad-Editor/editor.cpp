#include <fstream>
#include <iostream>
#include <stdlib.h>


# include "myconsole.h"
# include "editor.h"
#include "Doubly-Linked-List.h"
using namespace std;

//-------------------------------POINT CLASS------------------------------//
//initialize MaxPoint
point point::MaxPoint(MAX_X,MAX_Y); 
bool point::incrementX()
{
	bool returnValue = true;
	if (x<MaxPoint.x)
		x++;
	else if (y<MaxPoint.y)
	{
		x=0;
		y=y+1;
	}
	else
		returnValue = false;

	return returnValue;
}

bool point::incrementY()
{
	bool returnValue = true;
	if (y<MaxPoint.y)
		y++;
	else
		returnValue = false;

	return returnValue;

}
bool point::decrementX()
{
	bool returnValue = true;
	if (x>0)
		x--;
	else if (y>0)
	{
		y--;
		x=MaxPoint.x;
	}
	else
		returnValue = false;

	return returnValue;
}
bool point::decrementY()
{
	bool returnValue = true;
	if (y>0)
		y--;
	else
		returnValue = false;

	return returnValue;

}

//-------------------------------END OF POINT CLASS


int mainEditor()
{	
	int key = 0;
	bool stop = false;
	point currentPosition(0,0);

	Double_List <char>e_link; //Editor Link List (e_link)
	Double_List<char>::iter e_iterator; //Editor Iterator


		int word_count=0; //Used in Display Function , keep track of Characters 
		point temp(0,0); //Used to temporary hold the location of cursor
		bool check_temp=false; //Check for valid location
		bool check_insertion=false;	//Check for valid insertion
		bool check_delete=false;	//Check for valid Deletion

	currentPosition.setMaxPoint(MAX_X,MAX_Y);
	bool specialKey = false;
	
	e_link.Display(currentPosition,word_count); //Linked List Display Function 

	while(!stop)
	{
		
		key = CheckWhichKeyPressed(specialKey);

		//escape key
		if (key==ESCKEY)
			stop=true;
		//printable character...only adds to the end of text
		//this will not do insertions in between text
		//add code here to insert characters within text
		else if (!specialKey&&key>=32&&key<=126)
		{
			
					e_iterator=e_link.insert(e_iterator,key,currentPosition,check_insertion);
			if(check_insertion==false) cout << (char)key;
			else 
			{
					e_link.Print();
			}
					check_insertion=false;
					currentPosition.incrementX();
					word_count++;
					e_link.Display(currentPosition,word_count);
		}
		else if (specialKey&&key==LEFTKEY && e_link.isEmpty()==false)
		{
					temp=currentPosition;
					temp.decrementX();
					check_temp=e_link.Search(e_iterator,temp,'L');

			if(check_temp==true) 
			{
					currentPosition.decrementX();
					e_link.Display(currentPosition,word_count);
			}
		}
		else if (specialKey&&key==RIGHTKEY && e_link.isEmpty()==false)
		{
					temp=currentPosition;
					temp.incrementX();
					check_temp=e_link.Search(e_iterator,temp,'R');

			if(check_temp==true) 
			{
					currentPosition.incrementX();
					e_link.Display(currentPosition,word_count);
			}
		}
		else if (specialKey&&key==UPKEY && e_link.isEmpty()==false)
		{
					temp=currentPosition;
					temp.decrementY();
					check_temp=e_link.Search(e_iterator,temp,'U');

			if(check_temp==true) 
			{
					currentPosition.decrementY();
					e_link.Display(currentPosition,word_count);
			}
			
		}
		else if (specialKey&&key==DOWNKEY && e_link.isEmpty()==false)
		{
					temp=currentPosition;
					temp.incrementY();
					check_temp=e_link.Search(e_iterator,temp,'D');

			if(check_temp==true) 
			{	
					currentPosition.incrementY();
					e_link.Display(currentPosition,word_count);
			}
		}

		else if (key == DELKEY)
		{
					e_iterator=e_link.erase(e_iterator,currentPosition,'D',check_delete,word_count);
//call a function to handle 
			if(check_delete==true)
			{
				
					e_link.Print();
					check_delete=false;
			}
					e_link.Display(currentPosition,word_count);
		}
		else if (key == BACKSPACE)
		{
			//handle backspace here

					e_iterator=e_link.erase(e_iterator,currentPosition,'B',check_delete,word_count);
//call a function to handle 
			if(check_delete==true)
			{
					e_link.Print();
					check_delete=false;
				
			}
					e_link.Display(currentPosition,word_count);
		}
		else if (key == F1KEY)
		{
					e_link.Print();
					e_link.Display(currentPosition,word_count);
			//handle search here
			//you can take the cursor at the bottom of the screen and get some input
			//for searching
					e_link.Search_Word(e_iterator,currentPosition);
		}
		else if (key == F2KEY)
		{
			//save to file using iterators
					HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
					e_link.Display(currentPosition,word_count);

					ofstream outfile("myeditor.txt");
			if(outfile.is_open())
			{
					Double_List<char>::iter it; //Used to iterate from head to tail 

				for(it=e_link.begin();it!=e_link.end();++it)
				{
					outfile<<*it;
				}
					outfile<<*it;

					PlaceCursor(0,22);
					SetConsoleTextAttribute(console, 128);
					cout<<"Saved Successfully!";
					SetConsoleTextAttribute(console, 7);
			}
			else 
			{
					PlaceCursor(0,22);
					SetConsoleTextAttribute(console, 128);
					cout<<"Can't Open File!";
					SetConsoleTextAttribute(console, 7);
			}
		}
		PlaceCursor(currentPosition.getX(),currentPosition.getY());
	}
	
	return 0;
}	


int main()
{
	
	mainEditor();
	return 0;
}
