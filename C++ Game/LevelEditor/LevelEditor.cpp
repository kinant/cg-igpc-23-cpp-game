#include <iostream>
#include <conio.h>
#include <fstream>

using std::cout;
using std::cin;
using std::endl;

using std::string;

using std::ofstream;

constexpr char kCursor = '_';

constexpr char kTopRightBorder = 187;
constexpr char kTopLeftBorder = 201;
constexpr char kBottomRightBorder = 188;
constexpr char kBottomLeftBorder = 200;
constexpr char kHorizontalBorder = 205;
constexpr char kVerticalBorder = 186;

constexpr int kArrowInput = 224;
constexpr int kLeftArrow = 75;
constexpr int kRightArrow = 77;
constexpr int kUpArrow = 72;
constexpr int kDownArrow = 80;

constexpr int kEscape = 27;
constexpr int kBackspace = 8;



void GetLevelDimensions(int& Width, int& Height);
void DisplayLevel(char* pLevel, const int Width, const int Height, const int CursorX, const int CursorY);
int GetIndexFromXY(const int X, const int Y, const int Width);

void DisplayTopBorder(const int Width);
void DisplayBottomBorder(const int Width);
void DisplayLeftBorder();
void DisplayRightBorder();

bool EditLevel(char* pLelvel, int& CursorX, int& CursorY, const int Width, const int Height);
void SaveLevel(char* pLevel, const int Width, const int Height);

void DisplayLegend();

int main()
{
	int LevelWidth;
	int LevelHeight;

	GetLevelDimensions(LevelWidth, LevelHeight);

	char* pLevel = new char[LevelWidth * LevelHeight];
	
	for (int i = 0; i < LevelWidth * LevelHeight; i++) 
	{
		pLevel[i] = ' ';
	}

	int CursorX = 0;
	int CursorY = 0;

	bool bDoneEditing = false;

	while(!bDoneEditing)
	{
		system("CLS");
		DisplayLevel(pLevel, LevelWidth, LevelHeight, CursorX, CursorY);
		DisplayLegend();
		bDoneEditing = EditLevel(pLevel, CursorX, CursorY, LevelWidth, LevelHeight);
	}

	system("CLS");
	DisplayLevel(pLevel, LevelWidth, LevelHeight, -1, -1);

	SaveLevel(pLevel, LevelWidth, LevelHeight);

	delete[] pLevel;
	pLevel = nullptr;
}


void DisplayLegend() 
{
	cout << "Arrows to move cursor" << endl;
	cout << "ESC to finish editing" << endl;
	cout << "+ | - for walls" << endl;
	cout << "@ for player start" << endl;
	cout << "r g b for key" << endl;
	cout << "R G B for door" << endl;
	cout << "$ for money" << endl;
	cout << "v for vertical moving enemy" << endl;
	cout << "h for horizontal moving enemy" << endl;
	cout << "e for non-moving enemy" << endl;
	cout << "X for goal" << endl;
}

void SaveLevel(char* pLevel, const int Width, const int Height) 
{
	cout << "Please input file name to save level (eg. Level1.txt): ";

	string LevelName;

	cin >> LevelName;

	LevelName.insert(0, "../");

	ofstream LevelFile;
	LevelFile.open(LevelName);

	if (!LevelFile) 
	{
		cout << "Opening of Level File Failed!" << endl;
	}
	else 
	{
		LevelFile << Width << endl;
		LevelFile << Height << endl;

		LevelFile.write(pLevel, Width * Height);

		if (!LevelFile) 
		{
			cout << "Writing to File Failed!" << endl;
		}
		
		LevelFile.close();
	}
}

bool EditLevel(char* pLelvel, int& CursorX, int& CursorY, const int Width, const int Height) 
{
	int NewCursorX = CursorX;
	int NewCursorY = CursorY;

	int IntInput = _getch();

	if (IntInput == kArrowInput) 
	{
		int ArrowInput = _getch();

		switch (ArrowInput) 
		{
			case kLeftArrow:
			{
				NewCursorX--;
				break;
			}
			case kRightArrow:
			{
				NewCursorX++;
				break;
			}
			case kUpArrow:
			{
				NewCursorY--;
				break;
			}
			case kDownArrow:
			{
				NewCursorY++;
				break;
			}
			default:
				break;
		}

		if (NewCursorX < 0) 
		{
			NewCursorX = 0;
		}
		else if (NewCursorX == Width) 
		{
			NewCursorX = Width - 1;
		}

		if (NewCursorY < 0)
		{
			NewCursorY = 0;
		}
		else if (NewCursorY == Height)
		{
			NewCursorY = Height - 1;
		}

		CursorX = NewCursorX;
		CursorY = NewCursorY;
	}
	else 
	{
		if (IntInput == kEscape) 
		{
			return true;
		}
		else if (IntInput == kBackspace) {
			// ignore
		}
		else 
		{
			int Index = GetIndexFromXY(NewCursorX, NewCursorY, Width);
			pLelvel[Index] = (char)IntInput;
		}
	}

	return false;
}

void GetLevelDimensions(int& Width, int& Height)
{
	cout << "Enter the width of your level: ";
	cin >> Width;

	cout << "Enter the height of your level: ";
	cin >> Height;
}

void DisplayLevel(char* pLevel, const int Width, const int Height, const int CursorX, const int CursorY)
{
	DisplayTopBorder(Width);

	for (int Y = 0; Y < Height; Y++) 
	{
		DisplayLeftBorder();

		for(int X = 0; X < Width; X++) 
		{
			if (CursorX == X && CursorY == Y) 
			{
				cout << kCursor;
				continue;
			}
			const int Index = GetIndexFromXY(X, Y, Width);
			cout << pLevel[Index];
		}

		DisplayRightBorder();

	}


	DisplayBottomBorder(Width);
}

void DisplayTopBorder(const int Width) 
{
	cout << kTopLeftBorder;
	
	for (int i = 0; i < Width; i++) 
	{
		cout << kHorizontalBorder;
	}

	cout << kTopRightBorder << endl;
}

void DisplayBottomBorder(const int Width) 
{
	cout << kBottomLeftBorder;

	for (int i = 0; i < Width; i++)
	{
		cout << kHorizontalBorder;
	}

	cout << kBottomRightBorder << endl;
}

void DisplayLeftBorder() 
{
	cout << kVerticalBorder;
}

void DisplayRightBorder() 
{
	cout << kVerticalBorder << endl;
}

int GetIndexFromXY(const int X, const int Y, const int Width) 
{
	return X + Y * Width;
}