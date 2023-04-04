#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"

#include <Windows.h>

class StateMachineExampleGame;

class GameplayState : public GameState
{
	public:
		GameplayState(StateMachineExampleGame* pOwner);

		virtual void Enter() override;
		virtual bool Update(bool processInput = true) override;
		virtual void Draw() override;

		static constexpr int kHUDWidth = 53;

	private:
		StateMachineExampleGame* m_pOwner;

		Player m_Player;
		Level m_Level;
		
		bool m_bBeatGame = false;
		int m_SkipFrameCount = 0;
		static constexpr int kFramesToSkip = 2;

		bool Load();
		void HandleCollision(const int PlayerX, const int PlayerY);
		void DrawHUD(const HANDLE& console);
};

