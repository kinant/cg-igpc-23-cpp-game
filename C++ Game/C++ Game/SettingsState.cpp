#include "SettingsState.h"

#include <iostream>
#include <conio.h>

#include "AudioManager.h"
#include "StateMachineExampleGame.h"

using std::cout;
using std::endl;

constexpr int kEscapeKey = 27;

constexpr char kSound = '1';
constexpr char kMainMenu = '2';

SettingState::SettingState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

bool SettingState::Update(bool ProcessInput)
{

	if (ProcessInput)
	{
		int Input = _getch();

		if (Input == kEscapeKey || static_cast<char>(Input) == kMainMenu)
		{
			m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
		}
		else if (static_cast<char>(Input) == kSound)
		{
			AudioManager::GetInstance()->ToggleSound();
			AudioManager::GetInstance()->PlayMoneySound();
		}
	}

	return false;
}

void SettingState::Draw() const
{
	system("CLS");
	cout << endl << endl << endl;
	cout << "           - - - SETTINGS - - -" << endl << endl;
	cout << "               " << kSound << ". Toggle Sound ";

	if (AudioManager::GetInstance()->IsSoundOn()) 
	{
		cout << "(ON)" << endl;
	}
	else 
	{
		cout << "(OFF)" << endl;
	}

	cout << "               " << kMainMenu << ". Back to Main Menu " << endl;
}