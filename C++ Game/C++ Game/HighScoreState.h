#pragma once
#include "GameState.h"
#include <set>

class StateMachineExampleGame;

class HighScoreState : public GameState
{
	public:
		HighScoreState(StateMachineExampleGame* pOwner);
		~HighScoreState() = default;
		virtual bool Update(bool ProcessInput = true) override;
		virtual void Draw() override;

	private:
		StateMachineExampleGame* m_pOwner = nullptr;
		std::set<int> m_HighScores{};
		
};

