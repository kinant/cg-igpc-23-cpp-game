#pragma once
#include "AActor.h"

class Enemy : public AActor 
{
	public:
		Enemy(const int X, const int Y, const int DeltaX = 0, const int DeltaY = 0);

		virtual ActorType GetType() const override { return ActorType::Enemy; }
		virtual void Draw() const override;
		virtual void Update() override;

	private:
		int m_MovementInX;
		int m_MovementInY;

		int m_CurrentMovementX;
		int m_CurrentMovementY;

		int m_DirectionX;
		int m_DirectionY;

		void UpdateDirection(int& Current, int& Direction, const int& Movement);
};