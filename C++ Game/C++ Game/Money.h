#pragma once
#include "AActor.h"

class Money : public AActor 
{
	public:
		Money(const int X, const int Y, const int Worth);

		int GetWorth() const { return m_Worth; }

		virtual ActorType GetType() const override { return ActorType::Money; }
		virtual void Draw() const override;

	private:
		int m_Worth;
};
