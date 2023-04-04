#include "Game.h"
#include <conio.h>
#include <Windows.h>
#include <fstream>
#include <assert.h>

#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"

#include "AudioManager.h"

Game::Game()
	: m_bIsGameOver(false)
    , m_bUserQuit(false)
{

}
Game::~Game() 
{

}


void Game::Run() 
{
	Draw();

	m_bIsGameOver = Update();

	if (m_bIsGameOver) 
	{
		Draw();
	}
}