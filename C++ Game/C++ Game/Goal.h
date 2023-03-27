#pragma once
#include "AActor.h"

class Goal : public AActor 
{
	public:
		Goal(const int X, const int Y);
		
		virtual ActorType GetType() const override { return ActorType::Goal; }
		virtual void Draw() const override;
};