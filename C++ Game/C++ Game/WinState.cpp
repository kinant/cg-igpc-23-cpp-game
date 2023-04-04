#include "WinState.h"
#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using std::cout;
using std::endl;

WinState::WinState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{

}

bool WinState::Update(bool ProcessInput)
{
	if (ProcessInput)
	{
		int Input = _getch();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	return false;
}

void WinState::Draw()
{
	system("CLS");
	cout << endl << endl << endl;
	cout << "           - - - WELL DONE - - -" << endl << endl;
	cout << "           You beat the game!" << endl << endl << endl;
	cout << "           Press any key to go back to main menu" << endl << endl;
}