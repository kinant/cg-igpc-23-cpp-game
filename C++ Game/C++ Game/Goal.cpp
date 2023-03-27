#include <iostream>
#include "Goal.h"

Goal::Goal(const int X, const int Y) 
	: AActor(X, Y)
{

}

void Goal::Draw() const
{
	std::cout << "X";
}