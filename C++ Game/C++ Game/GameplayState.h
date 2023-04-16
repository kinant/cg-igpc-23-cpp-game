#pragma once
#include "GameState.h"
#include "Player.h"
#include "Level.h"
#include <vector>
#include <string>

#include <Windows.h>

class StateMachineExampleGame;

class GameplayState : public GameState
{
	public:
		GameplayState(StateMachineExampleGame* pOwner);
		~GameplayState();

		virtual void Enter() override;
		virtual bool Update(bool processInput = true) override;
		virtual void Draw() override;

		static constexpr int kHUDWidth = 53;

	private:
		StateMachineExampleGame* m_pOwner = nullptr;

		Player m_Player;
		Level* m_pLevel = nullptr;
		
		bool m_bBeatLevel = false;
		int m_SkipFrameCount = 0;
		static constexpr int kFramesToSkip = 2;

		int m_currentLevel = 0;
		std::vector<std::string> m_LevelNames;

		bool Load();
		void HandleCollision(const int PlayerX, const int PlayerY);
		void DrawHUD(const HANDLE& console);
};

