#include "MainMenuState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"

using std::cout;
using std::endl;

constexpr int kEscapeKey = 27;

constexpr char kPlay = '1';
constexpr char kHighScore = '2';
constexpr char kSettings = '3';
constexpr char kQuit = '4';

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
		else if (static_cast<char>(Input) == kHighScore)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Highscore);
		}
		else if (static_cast<char>(Input) == kSettings)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Settings);
		}
	}

	return bShouldQuit;
}

void MainMenuState::Draw()
{
	system("CLS");
	cout << endl << endl << endl;
	cout << "           - - - MAIN MENU - - -" << endl << endl;
	cout << "               " << kPlay << ". Play " << endl;
	cout << "               " << kHighScore << ". High Scores " << endl;
	cout << "               " << kSettings << ". Settings " << endl;
	cout << "               " << kQuit << ". Quit " << endl;
}

