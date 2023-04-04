#include "MainMenuState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using std::cout;
using std::endl;
using std::cin;

constexpr int kEscapeKey = 27;

constexpr char kPlay = '1';
constexpr char kQuit = '2';

MainMenuState::MainMenuState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{

}

bool MainMenuState::Update(bool ProcessInput)
{
	bool bShouldQuit = false;

	if (ProcessInput) 
	{
		int Input = _getch();

		if (Input == kEscapeKey || static_cast<char>(Input) == kQuit) 
		{
			bShouldQuit = true;
		}
		else if (static_cast<char>(Input) == kPlay) 
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Gameplay);
		}
	}

	return bShouldQuit;
}

void MainMenuState::Draw() const
{
	system("CLS");
	cout << endl << endl << endl;
	cout << "           - - - MAIN MENU - - -" << endl << endl;
	cout << "				" << kPlay << ". Play " << endl;
	cout << "				" << kQuit << ". Quit " << endl;
}

