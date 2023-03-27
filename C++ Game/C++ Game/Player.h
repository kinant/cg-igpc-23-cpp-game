#pragma once
#include "AActor.h"

// forward class declaration
class Key;

#include "Point.h"

static constexpr char kPlayerSymbol = '@';
constexpr int kStartingNumberOfLives = 3;

class Player : public AActor
{
	public:
		Player();

		bool HasKey() const;
		bool HasKey(const ActorColor Color) const;
		void PickupKey(Key* Key);
		void UseKey();
		void DropKey();

		void AddMoney(const int Money) { m_Money += Money; }
		int GetMoney() const { return m_Money; }

		int GetLives() const { return m_Lives; };
		void DecrementLives() { m_Lives--; }

		virtual ActorType GetType() const override { return ActorType::Player; }
		virtual void Draw() const override;

	private:
		Key* m_pCurrentKey;
		int m_Money;
		int m_Lives;
};