#pragma once
#include "AActor.h"

class Door : public AActor
{
public:
	Door(const int X, const int Y, const ActorColor ClosedColor, const ActorColor OtherColor);

	virtual void Draw() const override;

	virtual ActorType GetType() const override { return ActorType::Door; }

	bool IsOpen() const { return m_bIsOpen; }
	void Open() { m_bIsOpen = true; }
	ActorColor GetColor() const { return m_ClosedColor;  }

private:
	bool m_bIsOpen;
	ActorColor m_ClosedColor;
	static constexpr char DOR = (char)219;
};