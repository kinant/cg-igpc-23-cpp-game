#pragma once
#include "GameState.h"

class StateMachineExampleGame;

class SettingState : public GameState
{
	public:
		SettingState(StateMachineExampleGame* pOwner);
		~SettingState() = default;
		virtual bool Update(bool ProcessInput = true) override;
		virtual void Draw() const override;

	private:
		StateMachineExampleGame* m_pOwner;
};

