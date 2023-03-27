#pragma once
#include "AActor.h"

class Key : public AActor {
	public:
		Key(const int X, const int Y, const ActorColor Color)
			: AActor(X, Y, Color) 
		{
		
		}

		virtual ActorType GetType() const override { return ActorType::Key; }
		virtual void Draw() const override;
};