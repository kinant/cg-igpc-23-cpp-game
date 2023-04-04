#include "Game.h"

Game::Game()
{

}
Game::~Game() 
{

}

void Game::Initialize(GameStateMachine* pStateMachine)
{
	if (pStateMachine != nullptr) 
	{
		pStateMachine->Init();
		m_pGameStateMachine = pStateMachine;
	}
}

void Game::RunGameLoop()
{
	bool bIsGameOver = false;

	while (!bIsGameOver) 
	{
		Update(false);
		Draw();
		bIsGameOver = Update();
	}
	Draw();
}

void Game::Deinitialize()
{
	if (m_pGameStateMachine) 
	{
		m_pGameStateMachine->CleanUp();
	}
}

bool Game::Update(bool processInput)
{
	return m_pGameStateMachine->UpdateCurrentState(processInput);
}

void Game::Draw() const
{
	m_pGameStateMachine->DrawCurrentState();
}

