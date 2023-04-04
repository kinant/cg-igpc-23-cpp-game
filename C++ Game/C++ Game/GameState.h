#pragma once

class GameState 
{
	public:
		virtual ~GameState() = default; // Q&A: what is this?

		virtual void Enter() {}
		virtual bool Update(bool processInput = true) { return false; }
		virtual void Draw() const = 0;

		virtual void Exit() {}
};