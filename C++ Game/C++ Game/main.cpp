#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>

#include <iostream>
#include "Game.h"
#include "StateMachineExampleGame.h"

#include "AudioManager.h"

using std::cout;
using std::endl;

int main() 
{
	// _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	Game MyGame;

	StateMachineExampleGame GameStateMachine(&MyGame);

	MyGame.Initialize(&GameStateMachine);
	MyGame.RunGameLoop();
	MyGame.Deinitialize();

	AudioManager::DestroyInstance();

	// Check for Memory Leaks
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
	_CrtDumpMemoryLeaks();

	return 0;
}
