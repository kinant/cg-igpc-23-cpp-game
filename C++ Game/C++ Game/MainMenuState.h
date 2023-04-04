#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class MainMenuState : public GameState
{
	public:
		MainMenuState(StateMachineExampleGame* pOwner);
		~MainMenuState() = default;
		virtual bool Update(bool ProcessInput = true) override;
		virtual void Draw() override;

	private:
		StateMachineExampleGame* m_pOwner = nullptr;
};

