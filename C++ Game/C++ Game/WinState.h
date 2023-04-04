#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class WinState : public GameState
{
	public:
		WinState(StateMachineExampleGame* pOwner);
		~WinState() = default;
		virtual bool Update(bool ProcessInput = true) override;
		virtual void Draw() override;

	private:
		StateMachineExampleGame* m_pOwner = nullptr;
};

