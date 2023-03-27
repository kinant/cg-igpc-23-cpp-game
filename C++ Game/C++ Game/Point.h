#pragma once
struct Point 
{
	int X;
	int Y;

	Point() 
		: X(0)
		, Y(0)
	{
		
	}

	Point(int X, int Y) 
	{
		this->X = X;
		this->Y = Y;
	}
};