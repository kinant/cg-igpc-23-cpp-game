#include<iostream>
#include<Windows.h>

#include "Player.h"
#include "Key.h"

#include "AudioManager.h"

Player::Player() 
	: AActor(0, 0)
	, m_pCurrentKey(nullptr)
	, m_Money(0)
	, m_Lives(kStartingNumberOfLives)
{

}

bool Player::HasKey() const
{
	return (m_pCurrentKey != nullptr);
}

bool Player::HasKey(const ActorColor Color) const
{
	return (HasKey() && m_pCurrentKey->GetColor() == Color);
}

void Player::PickupKey(Key* Key) 
{
	m_pCurrentKey = Key;
}

void Player::UseKey() 
{
	m_pCurrentKey->Remove();
	m_pCurrentKey = nullptr;
}

void Player::DropKey() 
{
	if (m_pCurrentKey) 
	{
		m_pCurrentKey->Place(m_pPosition->X, m_pPosition->Y);
		m_pCurrentKey = nullptr;

		AudioManager::GetInstance()->PlayKeyPickupSound();
	}
}

void Player::Draw() const
{
	std::cout << kPlayerSymbol;
}