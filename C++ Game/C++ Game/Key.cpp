#include <iostream>
#include <Windows.h>

#include "Key.h"

void Key::Draw() const
{
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(console, (int)m_Color);

	std::cout << "+";

	SetConsoleTextAttribute(console, (int)ActorColor::Regular);
}