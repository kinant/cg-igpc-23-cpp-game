#include <iostream>

#include "Game.h"
#include "AudioManager.h"

using std::cout;
using std::endl;

int main() 
{
	Game MyGame;

	if (MyGame.Load()) 
	{
		while (!MyGame.IsGameOver()) 
		{
			MyGame.Run();
		}

		if (MyGame.DidUserQuit()) 
		{
			cout << "Thanks for playing!" << endl;
		}
		else if (MyGame.GetPlayerLives() < 0) 
		{
			cout << "YOU LOSE!!!" << endl;
			AudioManager::GetInstance()->PlayLoseSound();
		}
		else 
		{
			cout << "YOU WON!!!" << endl;
			AudioManager::GetInstance()->PlayWinSound();
		}
	}
	else 
	{
		cout << "Game did not load. Terminating now!" << endl;
	}

	AudioManager::DestroyInstance();

	return 0;
}
