#include <iostream>

#include "Game.h"
#include "StateMachineExampleGame.h"

#include "AudioManager.h"

using std::cout;
using std::endl;

int main() 
{
	Game MyGame;

	StateMachineExampleGame GameStateMachine(&MyGame);

	MyGame.Initialize(&GameStateMachine);
	MyGame.RunGameLoop();
	MyGame.Deinitialize();

	AudioManager::DestroyInstance();

	return 0;
}
