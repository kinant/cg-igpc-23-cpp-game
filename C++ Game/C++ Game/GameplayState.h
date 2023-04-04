#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"

class StateMachineExampleGame;

class GameplayState : public GameState
{
	public:
		GameplayState(StateMachineExampleGame* pOwner);

		virtual void Enter() override;
		virtual bool Update(bool processInput = true) override;
		virtual void Draw() const override;

	private:
		StateMachineExampleGame* m_pOwner;

		Player m_Player;
		Level m_Level;
		
		bool m_bBeatGame = false;
		int m_SkipFrameCount = 0;
		static constexpr int kFramesToSkip = 2;


		bool Load();
		bool HandleCollision(const int PlayerX, const int PlayerY);
};

