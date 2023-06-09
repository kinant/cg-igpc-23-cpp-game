#pragma once
#include<iostream>
#include <vector>

class AActor;

using std::string;

class Level 
{
	public:

		static constexpr char WAL = static_cast<char>(219);

		Level();
		~Level();
		
		bool Load(string LevelName, int* PlayerX, int* PlayerY);
		void Draw() const;

		bool IsSpace(int X, int Y) const;
		bool IsWall(int X, int Y) const;

		int GetHeight() const { return m_Height; }
		int GetWidth() const { return m_Width; }

		AActor* UpdateActors(int X, int Y);

	private:
		char* m_pLevelData =  nullptr;
		int m_Height = 0;
		int m_Width = 0;

		std::vector<AActor*> m_pActors;

		bool Convert(int* PlayerX, int* PlayerY);
		int GetIndexFromCoordinates(int X, int Y) const;
};