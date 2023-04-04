#include "GameplayState.h"

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
#include "Utility.h"

#include "StateMachineExampleGame.h"

using std::cout;
using std::endl;
using std::string;
using std::ifstream;

static constexpr int kOpenDoorColor = 10;
static constexpr int kClosedDoorColor = 12;
static constexpr int kRegularColor = 7;

static constexpr int kArrowInput = 224;
static constexpr int kLeftArrow = 75;
static constexpr int kRightArrow = 77;
static constexpr int kUpArrow = 72;
static constexpr int kDownArrow = 80;
static constexpr int kEscapeKey = 27;

GameplayState::GameplayState(StateMachineExampleGame* pOwner)
	: m_pOwner(pOwner)
{
}

bool GameplayState::Load()
{
	return m_Level.Load("Level3.txt", m_Player.GetXPositionPointer(), m_Player.GetYPositionPointer());
}

void GameplayState::Enter() 
{
	Load();
}

bool GameplayState::Update(bool processInput)
{
    if (processInput && !m_bBeatGame)
    {
        int Input = _getch();
        int ArrowInput = 0;

        int NewPlayerX = m_Player.GetXPosition();
        int NewPlayerY = m_Player.GetYPosition();

        // one of the arrow keys was pressed
        if (Input == kArrowInput)
        {
            ArrowInput = _getch();
        }

        if ((Input == kArrowInput && ArrowInput == kLeftArrow) ||
            static_cast<char>(Input) == 'A' || static_cast<char>(Input) == 'a')
        {
            NewPlayerX--;
        }
        else if ((Input == kArrowInput && ArrowInput == kRightArrow) ||
            static_cast<char>(Input) == 'D' || static_cast<char>(Input) == 'd')
        {
            NewPlayerX++;
        }
        else if ((Input == kArrowInput && ArrowInput == kUpArrow) ||
            static_cast<char>(Input) == 'W' || static_cast<char>(Input) == 'w')
        {
            NewPlayerY--;
        }
        else if ((Input == kArrowInput && ArrowInput == kDownArrow) ||
            static_cast<char>(Input) == 'S' || static_cast<char>(Input) == 's')
        {
            NewPlayerY++;
        }
        else if (Input == kEscapeKey)
        {
            m_pOwner->LoadScene(StateMachineExampleGame::SceneName::MainMenu);
        }
        else if (static_cast<char>(Input) == 'Z' || static_cast<char>(Input) == 'z')
        {
            m_Player.DropKey();
        }

        // If position never changed
        if (NewPlayerX == m_Player.GetXPosition() && NewPlayerY == m_Player.GetYPosition())
        {
            
        }
        else
        {
            HandleCollision(NewPlayerX, NewPlayerY);
        }
    }

    if (m_bBeatGame)
    {
        ++m_SkipFrameCount;

        if (m_SkipFrameCount > kFramesToSkip)
        {
            m_SkipFrameCount = 0;

            Utility::WriteHighScore(m_Player.GetMoney());

            AudioManager::GetInstance()->PlayWinSound();
            m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Win);
        }
    }

    return false;
}

void GameplayState::HandleCollision(const int NewPlayerX, const int NewPlayerY)
{
    bool bIsGameDone = false;

    AActor* CollidedActor = m_Level.UpdateActors(NewPlayerX, NewPlayerY);

    if (CollidedActor != nullptr && CollidedActor->IsActive())
    {
        switch (CollidedActor->GetType())
        {
        case ActorType::Enemy:
        {
            Enemy* CollidedEnemy = dynamic_cast<Enemy*>(CollidedActor);
            assert(CollidedEnemy);

            AudioManager::GetInstance()->PlayLoseLifeSound();

            CollidedEnemy->Remove();
            m_Player.SetPosition(NewPlayerX, NewPlayerY);

            m_Player.DecrementLives();

            if (m_Player.GetLives() < 0)
            {
                AudioManager::GetInstance()->PlayLoseSound();
                m_pOwner->LoadScene(StateMachineExampleGame::SceneName::Lose);
            }

            break;
        }
        case ActorType::Money:
        {
            Money* CollidedMoney = dynamic_cast<Money*>(CollidedActor);
            assert(CollidedMoney);

            CollidedMoney->Remove();
            m_Player.AddMoney(CollidedMoney->GetWorth());
            m_Player.SetPosition(NewPlayerX, NewPlayerY);

            AudioManager::GetInstance()->PlayMoneySound();

            break;
        }
        case ActorType::Key:
        {
            Key* CollidedKey = dynamic_cast<Key*>(CollidedActor);
            assert(CollidedKey);

            if (!m_Player.HasKey())
            {
                m_Player.PickupKey(CollidedKey);
                CollidedKey->Remove();
                m_Player.SetPosition(NewPlayerX, NewPlayerY);
                AudioManager::GetInstance()->PlayKeyPickupSound();
            }

            break;
        }
        case ActorType::Door:
        {
            Door* CollidedDoor = dynamic_cast<Door*>(CollidedActor);
            assert(CollidedDoor);

            if (!CollidedDoor->IsOpen())
            {
                if (m_Player.HasKey(CollidedDoor->GetColor()))
                {
                    CollidedDoor->Open();
                    CollidedDoor->Remove();
                    m_Player.UseKey();
                    m_Player.SetPosition(NewPlayerX, NewPlayerY);

                    AudioManager::GetInstance()->PlayDoorOpenSound();
                }
                else
                {
                    AudioManager::GetInstance()->PlayDoorClosedSound();
                }
            }
            else
            {
                m_Player.SetPosition(NewPlayerX, NewPlayerY);
            }

            break;
        }
        case ActorType::Goal:
        {
            Goal* CollidedGoal = dynamic_cast<Goal*>(CollidedActor);
            assert(CollidedGoal);

            CollidedGoal->Remove();
            m_Player.SetPosition(NewPlayerX, NewPlayerY);
            m_bBeatGame = true;

            break;
        }
        default:
            break;
        }
    }
    else if (m_Level.IsSpace(NewPlayerX, NewPlayerY)) // no collision
    {
        m_Player.SetPosition(NewPlayerX, NewPlayerY);
    }
    else if (m_Level.IsWall(NewPlayerX, NewPlayerY))
    {
        AudioManager::GetInstance()->PlayDoorClosedSound();
    }
}

void GameplayState::Draw() const
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    system("CLS");

    m_Level.Draw();

    // set cursor for player
    COORD ActorCursorPosition;
    ActorCursorPosition.X = m_Player.GetXPosition();
    ActorCursorPosition.Y = m_Player.GetYPosition();
    SetConsoleCursorPosition(console, ActorCursorPosition);
    m_Player.Draw();

    // set cursor to the end of the level
    COORD CurrentCursorPosition;
    CurrentCursorPosition.X = 0;
    CurrentCursorPosition.Y = m_Level.GetHeight();
    SetConsoleCursorPosition(console, CurrentCursorPosition);
}