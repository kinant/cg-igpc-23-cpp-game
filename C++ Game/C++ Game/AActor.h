#pragma once
#include "Point.h"

enum class ActorColor 
{
	Regular = 7,
	Blue = 9,
	Green = 10,
	Red = 12,
	SolidGreen = 34,
	SolidRed = 68,
	SolidBlue = 153
};

enum class ActorType 
{
	Door,
	Enemy,
	Goal,
	Key,
	Money,
	Player
};

class AActor 
{
	public:
		AActor(int X, int Y, ActorColor = ActorColor::Regular);
		virtual ~AActor();

		int GetXPosition() const;
		int GetYPosition() const;
		int* GetXPositionPointer() const;
		int* GetYPositionPointer() const;
		void SetPosition(const int X, const int Y);

		ActorColor GetColor() const { return m_Color; }

		void Remove() { m_bIsActive = false; }
		bool IsActive() { return m_bIsActive;  }
		void Place(const int X, const int Y);

		virtual ActorType GetType() const = 0;
		virtual void Draw() const = 0;
		virtual void Update() 
		{
			
		}

	protected:
		Point* m_pPosition;

		bool m_bIsActive;
		ActorColor m_Color;
};