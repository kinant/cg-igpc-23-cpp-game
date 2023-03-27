#include "Enemy.h"

#include <iostream>

Enemy::Enemy(const int X, const int Y, const int DeltaX, const int DeltaY) 
	: AActor(X, Y)
	, m_CurrentMovementX(0)
	, m_CurrentMovementY(0)
	, m_DirectionX(0)
	, m_DirectionY(0)
	, m_MovementInX(DeltaX)
	, m_MovementInY(DeltaY)
{

	if (m_MovementInX != 0)
	{
		m_DirectionX = 1;
	}
	if (m_MovementInY != 0) 
	{
		m_DirectionY = 1;
	}
}

void Enemy::Draw() const
{
	std::cout << (char) 153;
}

void Enemy::Update() 
{
	if (m_MovementInX != 0) 
	{
		UpdateDirection(m_CurrentMovementX, m_DirectionX, m_MovementInX);
	}
	if (m_MovementInY != 0)
	{
		UpdateDirection(m_CurrentMovementY, m_DirectionY, m_MovementInY);
	}

	this->SetPosition(m_pPosition->X + m_DirectionX, m_pPosition->Y + m_DirectionY);
}

void Enemy::UpdateDirection(int& Current, int& Direction, const int& Movement) 
{
	Current += Direction;

	if (std::abs(Current) > Movement) 
	{
		Current = Movement * Direction;
		Direction *= -1;
	}

}