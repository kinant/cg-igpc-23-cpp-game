#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class SettingsState : public GameState
{
	public:
		SettingsState(StateMachineExampleGame* pOwner);
		~SettingsState() = default;
		virtual bool Update(bool ProcessInput = true) override;
		virtual void Draw() override;

	private:
		StateMachineExampleGame* m_pOwner;
};

