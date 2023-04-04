#pragma once
#include <iostream>
#include <set>
#include <string>
#include <fstream>
#include <iterator>

class Utility 
{
	public:
		static std::set<int> WriteHighScore(int score) 
		{
			// see if file exists and read the values
			std::string FileName = "highscores.txt";
			std::ifstream HighScoreFile(FileName);

			//Q&A: What is this?
			std::istream_iterator<int> Start(HighScoreFile), End;

			std::set<int> HighScores(Start, End);

			HighScoreFile.close();

			// if its empty, populate and save
			if (HighScores.size() == 0) 
			{
				HighScores.insert(100);
				HighScores.insert(50);
				HighScores.insert(20);
				HighScores.insert(10);
				HighScores.insert(5);
				
				std::ofstream OutFile(FileName);

				// Q&A: What is this?
				std::ostream_iterator<int> Output_Iterator(OutFile, "\n");
				
				// Q&A: What is this?
				std::copy(HighScores.begin(), HighScores.end(), Output_Iterator);
				OutFile.close();
			}

			// write the score
			HighScores.insert(score);

			// remove the lowest score
			HighScores.erase(HighScores.begin());

			// write the highscores
			std::ofstream OutFile(FileName);
			std::ostream_iterator<int> Output_Iterator(OutFile, "\n");
			std::copy(HighScores.begin(), HighScores.end(), Output_Iterator);
			OutFile.close();

			return HighScores;
		}
};