#include "HighScoreState.h"

#include <iostream>
#include <conio.h>

#include "StateMachineExampleGame.h"
#include "Utility.h"

using std::cout;
using std::endl;

HighScoreState::HighScoreState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
	m_HighScores = Utility::WriteHighScore(0);
}

bool HighScoreState::Update(bool ProcessInput)
{

	if (ProcessInput)
	{
		int Input = _getch();
		m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
	}
	return false;
}

void HighScoreState::Draw() const
{
	system("CLS");
	cout << endl << endl << endl;
	cout << "           - - - HIGH SCORES - - -" << endl << endl;
	
	// Q&A: What is going on in this loop?
	for (auto i = m_HighScores.rbegin(); i != m_HighScores.rend(); ++i) 
	{
		cout << "            " << *i << endl;
	}

	cout << endl << endl;
	cout << " Press any key to go back to Main Menu " << endl;
}
