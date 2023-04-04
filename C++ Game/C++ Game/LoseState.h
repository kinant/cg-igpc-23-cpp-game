#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class LoseState : public GameState
{
	public:
		LoseState(StateMachineExampleGame* pOwner);
		~LoseState() = default;
		virtual bool Update(bool ProcessInput = true) override;
		virtual void Draw() override;

	private:
		StateMachineExampleGame* m_pOwner = nullptr;
};

