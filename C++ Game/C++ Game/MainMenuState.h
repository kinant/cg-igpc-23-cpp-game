#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class MainMenuState : public GameState
{
	public:
		MainMenuState(StateMachineExampleGame* pOwner);
		~MainMenuState() = default;
		virtual bool Update(bool processInput = true) override;
		virtual void Draw() const override;

	private:
		StateMachineExampleGame* m_pOwner;
};

