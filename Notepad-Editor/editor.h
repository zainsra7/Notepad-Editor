#ifndef EDITOR_H
#define EDOTOR_H


const int MAX_X = 70;
const int MAX_Y = 15;


class point
{
public:
	point(){x=0;y=0;}
	point(int a,int b){x=a;y=b;}
	int getX(){return x;}
	int getY(){return y;}
	void set(int a,int b){x=a;y=b;}
	void setX(int a){x=a;}
	void setY(int b){y=b;}
	void setMaxPoint(int a,int b){MaxPoint.x=a;MaxPoint.y=b;}
	int getMaxPointX(){return MaxPoint.x;}
	int getMaxPointY(){return MaxPoint.y;}
	bool operator ==(point &b)
	{
		if(x==b.x && y==b.y) return true;
		return false;
	} 
	bool operator !=(point &b)
	{
		if(x==b.x && y==b.y) return false; 
		return true;
	}
	//increment x-coordinate.  If max limit is reached then increment y and set x to zero
	//return false if max limit for x and y is reached
	bool incrementX();
	//increment y-coordinate.  If max limit is reached return false
	bool incrementY();
	//decrement x-coordinate.  If x is already at 0 then go to line above at last x (decrement y)
	//return false if both x and y are at 0
	bool decrementX();
	//decrement y-coordinate.  If y is already at 0 then return false
	bool decrementY();
private:
	static point MaxPoint;
	int x;
	int y;

};

#endif