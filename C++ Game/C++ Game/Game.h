#pragma once
#include "GameStateMachine.h"

class Game 
{
	public:
		Game();
		~Game();
		
		void Initialize(GameStateMachine* pStateMachine);
		void RunGameLoop();
		void Deinitialize();

	private:
		GameStateMachine* m_pGameStateMachine = nullptr;
		bool Update(bool processInput = true);
		void Draw() const;
};