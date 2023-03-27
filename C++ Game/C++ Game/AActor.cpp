#include "AActor.h"

AActor::AActor(int X, int Y, ActorColor Color) 
	: m_pPosition(new Point(X, Y))
	, m_bIsActive(true)
	, m_Color(Color)
{
	
}

AActor::~AActor() 
{
	delete m_pPosition;
	m_pPosition = nullptr;
}

int AActor::GetXPosition() const
{
	return m_pPosition->X;
}

int AActor::GetYPosition() const
{
	return m_pPosition->Y;
}

int* AActor::GetXPositionPointer() const
{
	return &(m_pPosition->X);
}

int* AActor::GetYPositionPointer() const
{
	return &(m_pPosition->Y);
}

void AActor::SetPosition(const int X, const int Y) 
{
	m_pPosition->X = X;
	m_pPosition->Y = Y;
}

void AActor::Place(const int X, const int Y) 
{
	AActor::SetPosition(X, Y);
	m_bIsActive = true;
}