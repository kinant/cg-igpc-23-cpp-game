#include <fstream>
#include <Windows.h>
#include <assert.h>

#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "Key.h"
#include "Door.h"
#include "Goal.h"
#include "Money.h"


using std::cout;
using std::cin;
using std::endl;

using std::ifstream;

Level::Level()
	: m_pLevelData(nullptr)
	, m_Width(0)
	, m_Height(0)
{
}

Level::~Level()
{
	if (m_pLevelData != nullptr) 
	{
		delete[] m_pLevelData;
		m_pLevelData = nullptr;
	}

    while (!m_pActors.empty()) 
    {
        delete m_pActors.back();
        m_pActors.pop_back();
    }
}

bool Level::Load(string LevelName, int* PlayerX, int* PlayerY)
{
    LevelName.insert(0, "../");

    ifstream LevelFile;
    LevelFile.open(LevelName);

    if (!LevelFile)
    {
        cout << "Opening file failed!" << endl;
        return false;
    }
    else
    {
        constexpr int TempSize = 25;
        char Temp[TempSize];

        LevelFile.getline(Temp, TempSize, '\n');
        m_Width = atoi(Temp);

        LevelFile.getline(Temp, TempSize, '\n');
        m_Height = atoi(Temp);

        m_pLevelData = new char[m_Width * m_Height];

        LevelFile.read(m_pLevelData, (long long) m_Width * m_Height);

        bool bAnyWarnings = Convert(PlayerX, PlayerY);

        if (bAnyWarnings)
        {
            cout << "There were some warnings in the level datta, see above." << endl;
            system("PAUSE");
        }

        return true;
    }
}

void Level::Draw() const
{
    HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(console, (int)ActorColor::Regular);

    // Draw the level
    for (int y = 0; y < m_Height; y++) 
    {
        for (int x = 0; x < m_Width; x++) 
        {
            int IndexToPrint = GetIndexFromCoordinates(x, y);
            cout << m_pLevelData[IndexToPrint];
        }
        cout << endl;
    }

    COORD ActorCursorPosition;

    // Draw actors
    for (auto Actor : m_pActors) 
    {
        if (Actor->IsActive()) 
        {
            ActorCursorPosition.X = Actor->GetXPosition();
            ActorCursorPosition.Y = Actor->GetYPosition();
            SetConsoleCursorPosition(console, ActorCursorPosition);
            Actor->Draw();
        }
    }
}

bool Level::IsSpace(int X, int Y) const
{
	return m_pLevelData[GetIndexFromCoordinates(X, Y)] == ' ';
}

bool Level::IsWall(int X, int Y) const 
{
    return m_pLevelData[GetIndexFromCoordinates(X, Y)] == WAL;
}

bool Level::Convert(int* PlayerX, int* PlayerY)
{
    bool bAnyWarnings = false;

    for (int Y = 0; Y < m_Height; Y++)
    {
        for (int X = 0; X < m_Width; X++) {
            int Index = GetIndexFromCoordinates(X, Y);

            switch (m_pLevelData[Index])
            {
            case '+':
            case '-':
            case '|':
            {
                m_pLevelData[Index] = WAL;
                break;
            }
            case 'r':
            {
                m_pLevelData[Index] = ' ';
                m_pActors.push_back(new Key(X, Y, ActorColor::Red));
                break;
            }
            case 'g':
            {
                m_pLevelData[Index] = ' ';
                m_pActors.push_back(new Key(X, Y, ActorColor::Green));
                break;
            }
            case 'b':
            {
                m_pLevelData[Index] = ' ';
                m_pActors.push_back(new Key(X, Y, ActorColor::Blue));
                break;
            }
            case 'R':
            {
                m_pLevelData[Index] = ' ';
                m_pActors.push_back(new Door(X, Y, ActorColor::Red, ActorColor::SolidRed));
                break;
            }
            case 'G':
            {
                m_pLevelData[Index] = ' ';
                m_pActors.push_back(new Door(X, Y, ActorColor::Green, ActorColor::SolidGreen));
                break;
            }
            case 'B':
            {
                m_pLevelData[Index] = ' ';
                m_pActors.push_back(new Door(X, Y, ActorColor::Blue, ActorColor::SolidBlue));
                break;
            }
            case 'X':
            {
                m_pLevelData[Index] = ' ';
                m_pActors.push_back(new Goal(X, Y));
                break;
            }
            case '$':
            {
                m_pLevelData[Index] = ' ';
                m_pActors.push_back(new Money(X, Y, 1 + rand() % 5));
                break;
            }
            case '@':
            {
                m_pLevelData[Index] = ' ';
                
                if (PlayerX != nullptr && PlayerY != nullptr) 
                {
                    *PlayerX = X;
                    *PlayerY = Y;
                }
                break;
            }
            case 'e':
            {
                m_pActors.push_back(new Enemy(X, Y));
                m_pLevelData[Index] = ' ';
                break;
            }
            case 'h':
            {
                m_pActors.push_back(new Enemy(X, Y, 3, 0));
                m_pLevelData[Index] = ' ';
                break;
            }
            case 'v':
            {
                m_pLevelData[Index] = ' ';
                m_pActors.push_back(new Enemy(X, Y, 0, 2));
                m_pLevelData[Index] = ' ';
                break;
            }
            case ' ':
            {
                break;
            }
            default:
                cout << "Invalid character in level file: " << m_pLevelData[Index] << endl;
                bAnyWarnings = true;
                break;
            }
        }
    }

    return bAnyWarnings;
}

int Level::GetIndexFromCoordinates(int X, int Y) const
{
    return X + Y * m_Width;
}

// updates all the actors and returns a colliding actor if there is one
AActor* Level::UpdateActors(int X, int Y) 
{
    AActor* CollidedActor = nullptr;

    for (auto Actor = m_pActors.begin(); Actor != m_pActors.end(); Actor++) 
    {
        (*Actor)->Update(); // Update all actors

        if (X == (*Actor)->GetXPosition() && Y == (*Actor)->GetYPosition()) 
        {
            // should only be able to collide with one actor
            assert(CollidedActor == nullptr);
            CollidedActor = (*Actor);
        }
    }

    return CollidedActor;
}
