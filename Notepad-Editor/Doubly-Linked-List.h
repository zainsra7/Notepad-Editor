#include <iostream>
#include <string>
#include<windows.h>
using namespace std;

template <typename T>
class Node
{
	point location;
	T data;
	Node<T> *next;
	Node<T> *prev;
	template <typename T>
	friend class Double_List;
	friend class My_Iterator;
public:
	Node()
	{
		next=nullptr;
		prev=nullptr;
	}
	~Node(){}
};

template <class T>
class Double_List
{
	Node<T> *head;
	Node<T> *tail;

	class My_Iterator
	{
		Node<T> *ptr;
	public: 
		My_Iterator()
		{
			ptr=NULL;
		}
		~My_Iterator()
		{}
		My_Iterator (My_Iterator &obj)
		{
			ptr=obj.ptr;
		}
		My_Iterator& operator =(My_Iterator &obj)
		{
		
				ptr=obj.ptr;
			
			return *this;
		}

		My_Iterator (Node<T> *p)
		{
			ptr=p;
		}
		My_Iterator& operator ++()
		{
			if(ptr) ptr=ptr->next;
			return *this;
		} 
		My_Iterator& operator --()
		{
			if(ptr) ptr=ptr->prev;
			return *this;
		}
		bool operator ==(const My_Iterator &it)
		{
			if(ptr==it.ptr) return true;
			 return false;
		}
		bool operator !=(const My_Iterator &it)
		{
			if(ptr!=it.ptr) return true;
			return false;
		}
		Node<T> operator ->(){return ptr;}
		T& operator *()
		{
			if(ptr) return ptr->data;
		}  

		void setdata(T item)
		{
			ptr->data=item;
		}
		void setlocation(int x,int y)
		{
			
			ptr->location.setX(x);
			ptr->location.setY(y);
		}
		Node<T>* get_ptr(){return ptr;}
		void set_ptr(Node<T>*p)
		{
			ptr=p;
		}
		T getdata()
		{
			return ptr->data;
		}
		point getlocation()
		{
			return ptr->location;
		}

	};

public:
	typedef My_Iterator iter;

//Constructor
	Double_List();

//Destructor
	~Double_List();

//copy_Constructor
	Double_List(const Double_List& obj);

//Assingment Operator (Deep Copy)
	Double_List<T>& operator =(const Double_List &obj);
	
//Return True if List is empty and vice versa
	bool isEmpty();

//will deallocate memory for all nodes of the list
	bool initialize();

//Print elements of List 
	void Print()
	{
				iter it(head);
				point temp(0,0);
				ClearScreen();
				for(;it!=tail; ++it)
				{
						temp=it.getlocation();
						PlaceCursor(temp.getX(),temp.getY());
						cout<<*it;
				}
						temp=it.getlocation();
						PlaceCursor(temp.getX(),temp.getY());
						cout<<*it;
	} 


//Display Function is a permanent bar shown at the end of editor , it shows 
//Current cursor position 
//Current # of characters 
//Screen Width and Height
//Other Prompting messages
	void Display(point Locate,int word_count)
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);	//Used for Colors
		PlaceCursor(0,20);
		for(int i=0;i<80;i++) cout<<"_";
		SetConsoleTextAttribute(console,128);
		for(int i=0;i<3;i++)
			for(int j=0;j<80;j++)
				cout<<" ";
		PlaceCursor(40,21);
		cout<<"Character_Count "<<word_count;
		PlaceCursor(40,22);
		cout<<"Cursor_pos"<<" "<<Locate.getX()<<","<<Locate.getY();
		PlaceCursor(60,21);
		cout<<"Window_Width   70";
		PlaceCursor(60,22);
		cout<<"Window_Height  15";
		PlaceCursor(0,23);
		for(int i=0;i<80;i++) cout<<"_";
		PlaceCursor(50,23);
		cout<<"F1-Search F2-Save ESC-Exit";
		SetConsoleTextAttribute(console,7);	//7 is default console color
	}

//Updating the location of characters/elements in the list , used for sliding left or right
	void Sliding(iter it,char type)
	{
		if(type=='L')	//Sliding towards left 
		{
			
			for(it;it!=tail;++it)
			{
				it.get_ptr()->location.decrementX();
			}	
				it.get_ptr()->location.decrementX();
		}
		else //Sliding towards right
		{
			for(it;it!=tail;++it)
			{
				it.get_ptr()->location.incrementX();
			}	
				it.get_ptr()->location.incrementX();
		}

	}

//Search function to Search for valid Location for the Cursor. (Cursor is updated to a valid location)
	bool Search(iter &it, point Locate,char check_for_right)
	{

//Exception for Down and Right direction (for Insertion after Tail , cursor can be moved back to black space after last character)
		if(check_for_right=='D' || check_for_right=='R')
		{
			point temp=tail->location;
			temp.incrementX();
			if(temp==Locate) 
			{
				it.set_ptr(tail);
				return true;
			}

		}

//Searches for valid lcations in the list 
		Node<T> *current=head;
		while(current && current->location !=Locate)
		{
			current=current->next;
		}
		if(current==nullptr) return false;
//Valid location found
		if(current->location==Locate) 
		{
			it.set_ptr(current);
			return true;
		}
		return false;
	}
//points the iterator to the start of list 
	iter begin()
	{
		iter a(head);
		return a;
	}

//points the iterator to the end of list
	iter end()
	{
		iter b(tail);
		return b;
	}

//deletes the item pointed to by that iterator and returns an iterator that points to the next position
//Locate is the Currentposition of Cursor. 
//type is the Type of erase e.g 'D' for Delete and 'B' for Backspace
//check_for_Sliding to se whether the list should be printed again upon returniing from function or not.
//word_count to update the number of elements in the list (Used in Display function)
	iter erase(iter &it,point &Locate,char type,bool &check_for_Sliding,int &word_count)
	{

//Check wheter the list is empty or not 

		if(!isEmpty())
	{
		if(type=='D')	//Handles the operation of Delete key
		{
//If Iterator is pointing at Head -Delete At Head

			if(head->location==Locate)
			{
//Only one element in List

					word_count--; //Decreasing Word_count

				if(head->next==nullptr) //Empty the List
				{
					delete head;
					head=tail=nullptr;
					it.set_ptr(nullptr);
					ClearScreen(); 			
				}

//More than One Element in List
				else 
				{
					Node<T> *temp=head;
					head=head->next;
					head->prev=nullptr;
					delete temp;
					it.set_ptr(head);
					
					check_for_Sliding=true;

					//Sliding Remaining Elements towards left

						Sliding(it,'L');
						it.set_ptr(head);
				}
			}//end of if(head->location==Locate)

//If Iterator is pointing at tail -Delete at Tail

			else if(tail->location==Locate)
			{
					Node<T>*temp=tail;
					tail->prev->next=nullptr;
					it.set_ptr(tail->prev);
					tail=tail->prev;
					delete temp;
					check_for_Sliding=true;
					word_count--; //Decreasing Word_count
			}	

//Deletion in the Middle 
			else if(Search(it,Locate,'S')) //Search Function to Check if Iterator is not pointing at Null , or Cursor is pointing to valid location
			{
				Node<T> *temp=it.get_ptr();
				temp->prev->next=temp->next;
				temp->next->prev=temp->prev;
				it.set_ptr(temp->next);
				delete temp;
				temp=it.get_ptr();

				check_for_Sliding=true;
				//Sliding
					Sliding(it,'L');
					it.set_ptr(temp);	
					word_count--; //Decreasing Word_count
			}

			
			
		} //end of if (type=='D') -Delete

//Handles the Backspace Operation of Editor 

		else if(type=='B')
		{

//Iterator is pointing to Head
			if(head->location==Locate) return it; 

//Iterator is pointing to the next of head. 

			point temp_point=head->location; //temp_point to store the location.
			temp_point.incrementX();

	if(temp_point==Locate)
			{
//Only One element in List

					word_count--; //Decreasing Word_count

				if(head->next==nullptr)
				{
					delete head;
					head=tail=nullptr;
					it.set_ptr(nullptr);
					ClearScreen();
				}
				else 
				{
//More than one element in List 

					Node<T> *temp=head;
					head=head->next;
					head->prev=nullptr;
					delete temp;
					it.set_ptr(head);

					check_for_Sliding=true;
				//Sliding 
					Sliding(it,'L');
					it.set_ptr(head);
				}
			} 
//Iterator is pointing to the next of tail.
			else 
			{
						word_count--; //Decreasing Word_count

						check_for_Sliding=true;
						temp_point=tail->location;
						temp_point.incrementX();

					if(temp_point==Locate)
					{
						
						Node<T> *temp=tail;
						tail=tail->prev;
						tail->next=nullptr;
						delete temp;
						it.set_ptr(tail);
					}

//Backspace/Delete in the Middle 
				else 
				{
					check_for_Sliding=true;
					Node<T> *temp=it.get_ptr()->prev;
					temp->prev->next=temp->next;
					temp->next->prev=temp->prev;
					delete temp;
					temp=it.get_ptr();
					
						Sliding(it,'L');
						it.set_ptr(temp);
				}
			
			}

			Locate.decrementX(); //Decrmenting the Cursor Position.

		} //end of else if(type=='B')

		
	} //end of If(!isEmpty())

		return it; //Returning Iterator back.
	}
	
//inserts an item prior to the location of the iterator and returns an iterator pointing to the newly inserted item
//Locate is the Currentposition of Cursor. 
//type is the Type of erase e.g 'D' for Delete and 'B' for Backspace
//check_for_Sliding to se whether the list should be printed again upon returniing from function or not.
	iter insert(iter &it,T item , point Locate,bool &check_for_Sliding)
	{
		Node<T> *temp=new Node<T>;
		temp->data=item;
		temp->location=Locate;
//When List is empty
		if(isEmpty()) 
		{
			head=tail=temp;
		}

//Insertion prior to Head Node
		else if(head->location==Locate)
		{
			temp->next=head;
			head->prev=temp;
			
			Sliding(it,'R');
			
			it.set_ptr(head);
			head=temp;
			check_for_Sliding=true;
			return it;
		}
//Only one element in List
		else if(head->next==nullptr)
		{
			head->next=temp;
			temp->prev=head;
			tail=temp;
		
		}
		else
		{
				Node<T> *current=it.get_ptr();
//Insertion prior to Iterator Position and updating iterator to newly position 
				if(current->next!=nullptr && current->prev!=nullptr && tail->location!=Locate)
			{
				current->prev->next=temp;
				temp->prev=current->prev;
				temp->next=current;
				current->prev=temp;

				check_for_Sliding=true;

				Sliding(it,'R');

				it.set_ptr(current);
				return it;
			}
//Insertion prior to Tail 
			else 
			{
				if(tail->location==Locate)
				{
					tail->prev->next=temp;
					temp->prev=tail->prev;
					temp->next=tail;
					tail->prev=temp;

					tail->location.incrementX();
					check_for_Sliding=true;
					return it;
				}
//Insertion after Tail 
				else 
				{
				current->next=temp;
				temp->prev=current;
				tail=temp;
				}
			}	
		}

		it.set_ptr(temp);
		return it;
	
		
	}

	bool Search_Word(iter &iterate,point &Locate)
	{
		HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE); //Used for Colors and Graphics

//If List is Empty
		if(isEmpty())
		{
			PlaceCursor(0,21);
			SetConsoleTextAttribute(console, 128);	//Grey background , Black Foreground
			cout<<"You have Entered Nothing yet!";
			SetConsoleTextAttribute(console, 7);
				return 0;
		}

		 iter it=head;	//Iterator it , used to iterate from head to tail
		string find_string;		//find_string to store string input from user

//Prompting for Input
		PlaceCursor(0,21);
	SetConsoleTextAttribute(console, 128);
		cout<<"Enter Thy String : ";
//getline to input string (terminating condition is Enter/Return Key)
		getline(cin,find_string,'\n');
		
		int length=find_string.length(); //To store the length of string
		bool found=false;    //Found flag
		int i=0;			//usd in indexing for find_string
		point location;		//used to store the location of string found 
		Node<T> *temp;		//Used to store the ptr/pointer of iterator
		int count=0;		//Used for keeping track of count

		while(it!=tail)
		{

			if(it.getdata()==find_string[i])
			{
				temp=it.get_ptr();
				location=it.getlocation();
				while(it.get_ptr()!=nullptr && it.getdata()==find_string[i])
				{
					count++;
					i++;
					++it;
				}
				if(count==length)
				{
					found=true;
					break;
				}
				i=0;
				count=0;
			}
			if(it.get_ptr()->next!=nullptr)
			++it;
		}

//If the character lies on tail 
		if(length==1 && tail->data==find_string[0])
		{
			SetConsoleTextAttribute(console, 128);
			PlaceCursor(0,22);
			cout<<"Found at "<<tail->location.getX()<<","<<tail->location.getY();

			Locate=tail->location;
			iterate.set_ptr(tail);

			PlaceCursor(40,22);
			cout<<"Cursor_pos"<<" "<<Locate.getX()<<","<<Locate.getY();
			SetConsoleTextAttribute(console, 7);
		}
//If String is found in text
		else if(found==true)
		{
//Update the Display 
			SetConsoleTextAttribute(console, 128);
			PlaceCursor(0,22);
			cout<<"Found at "<<location.getX()<<","<<location.getY();

//Higlight the found string
			PlaceCursor(location.getX(),location.getY());
			SetConsoleTextAttribute(console, 15+3*16);
			for(int i=0;i<find_string.length();i++)
				cout<<find_string[i];

//Updating Cursor Position
			Locate=location; 
//Updating Iterator
			iterate.set_ptr(temp);
//Updating Display 
			SetConsoleTextAttribute(console, 128);
			PlaceCursor(40,22);
			cout<<"Cursor_pos"<<" "<<Locate.getX()<<","<<Locate.getY();
			SetConsoleTextAttribute(console, 7);
		}
//If string not found, Updating the String. 
		else if(found==false)
		{
			SetConsoleTextAttribute(console, 128);
			PlaceCursor(0,22);
			cout<<"Nope,Not Found!";
			SetConsoleTextAttribute(console, 7);
		}

		return 0;
	}

};

//Implementation of Functions given Above 

//Doubly_Linked_list Functions 

	template <typename T>
	Double_List<T>::Double_List()
{
	head=tail=NULL;
}

	template <typename T>
	Double_List<T>::~Double_List()
	{
		initialize();
	}

	template <typename T>
	Double_List<T>::Double_List(const Double_List& obj)
	{
		if(obj.isEmpty) 
		{
			head=tail=NULL;
		} 
		else 
		{
			head=tail=NULL;
			Node<T> *current1=obj.head;
			Node<T> *current2=head;
			Node<T> *previous=head;
			
			current2->next=new Node<T>;
			current2=current2->next;
			current2->data=current1->data;
			current2->location=current1->location;

			while(current1!=NULL)
			{
				previous=current2;
				current2->next=new Node<T>;
				current2=current2->next;
				current2->data=current1->data;
				current2->location=current1->location;
				current2->prev=previous;
				current1=current1->next;
			}
			current2->next=NULL;
			tail=current2;
		}
	
	}

	template <typename T>
	Double_List<T>& Double_List<T>::operator=(const Double_List &obj)
	{
		if(this!=obj)
		{
			if(obj.isEmpty()) 
			{
				initialize();
			}
			else 
			{
				initialize();
				head=tail=NULL;
			Node<T> *current1=obj.head;
			Node<T> *current2=head;
			Node<T> *previous=head;
			
			current2->next=new Node<T>;
			current2=current2->next;
			current2->data=current1->data;
			current2->location=current1->location;

			while(current1!=NULL)
			{
				previous=current2;
				current2->next=new Node<T>;
				current2=current2->next;
				current2->data=current1->data;
				current2->location=current1->location;
				current2->prev=previous;
				current1=current1->next;
			}
			current2->next=NULL;
			tail=current2;
			}
		}
		return *this;
	}

	template <typename T>
	bool Double_List<T>::initialize()
	{
		if(!isEmpty())
	{
		Node<T> *current=head;
		Node<T> *temp=head;
		while(current!=NULL)
		{
			temp=current;
			current=current->next;
			delete temp;
		}
		head=tail=NULL;
		return true;
	}
	return false;
	}

	template <typename T>
	bool Double_List<T>::isEmpty()
	{
		if(head==nullptr) return true;
						return false;
	}

	
	




