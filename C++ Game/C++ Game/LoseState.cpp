#include "LoseState.h"
#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using std::cout;
using std::endl;

LoseState::LoseState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{

}

bool LoseState::Update(bool ProcessInput)
{
	if (ProcessInput)
	{
		int Input = _getch();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	return false;
}

void LoseState::Draw()
{
	system("CLS");
	cout << endl << endl << endl;
	cout << "           - - - GAME OVER - - -" << endl << endl;
	cout << "           Better luck next time!" << endl << endl << endl;
	cout << "           Press any key to go back to main menu" << endl << endl;
}