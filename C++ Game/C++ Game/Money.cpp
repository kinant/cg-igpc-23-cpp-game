#include <iostream>
#include "Money.h"

Money::Money(const int X, const int Y, const int Worth) 
	: AActor(X, Y)
	, m_Worth(Worth)
{
}

void Money::Draw() const 
{
	std::cout << "$";
}