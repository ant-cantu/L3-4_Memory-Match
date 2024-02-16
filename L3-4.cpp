//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
//* Program name    :	L3-4 (Memory Matching Game)							* 
//*																			* 
//* Written by      :	Anthony Cantu										* 
//*																			* 
//* Purpose         :	To play a game of memory match						* 
//*																			* 
//* Inputs          :	User selects a row and column until they find		*
//*						two matching values. Once all matches have been		*
//*						found, the game ends.								* 
//*																			* 
//* Outputs         :	Prompts user with instructions on how to select		*
//*						hidden values.										*
//*						Display hidden values masked by '*', once user		*
//*						selects a row and column, the hidden value is		*
//*						revealed.											*
//*						Prompts user is invalid selection is made.			* 
//*																			* 
//* Calls           :	initializeCards();									*
//*						initializePlaceHolder();							*
//*						validateSelection(char row,	char col);				*
//*						checkCard(char row, char col, bool firstChoice,		*
//*							int& score);                     				* 	
//*																			* 
//* Structure       :	BEGIN												* 
//*							Straight line code no sub-processes				* 
//*						STOP												* 
//*							End of Program									* 
//*																			* 
//*-------------------------------------------------------------------------* 
//* Collaboration   :	The Goonies											*
//*																			* 
//*-------------------------------------------------------------------------* 
//* Change Log:																* 
//*                         Revision										* 
//*       Date    Changed  Rel Ver Mod Purpose								* 
//* 10/17/23      acantu 000.000.000 Initial release of program       		* 
//*																			* 
//* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *
#include <iostream>
#include <cstdlib>
#include <iomanip>

//Using Statement
using namespace std;

//Function Prototypes
void initializeCards();
void initializePlaceholder();
bool validateSelection(char row, char col);
void checkCard(char row, char col, bool firstChoice, int& score);

//Global Definitions
namespace deck
{
	int table[4][4];
	int usedCard[8];
	char placeholder[4][4] = {	{'*', '*', '*', '*' },
								{'*', '*', '*', '*' },
								{'*', '*', '*', '*' },
								{'*', '*', '*', '*' }
	};
	int firstCard = 0;
	int firstRow = 0;
	int firstCol = 0;
};

//Global Variables
const bool FIRST_CHOICE = true;
const bool SECOND_CHOICE = false;

int main()
{
	char row, col;				//Variable to store entered row and column
	int score = 0;				//Initialize score to zero.
	char q;

	srand(time(0));

	cout << "Anthony Cantu\t" << "L3-4\t" << "L3-4.exe" << endl;

	initializePlaceholder();	//Initialize placerholder cards '*'
	initializeCards();			//Initialize value cards

	do 
	{
		do
		{
			cout << "Enter the row (1 to 4) and col (1 to 4) position of the pair: ";
			cin >> row >> col;
			cout << endl; //Line Break
			if (validateSelection(row, col))
				checkCard(row, col, FIRST_CHOICE, score);	//First choice
			else
				cout << "Invalid selection! Please try again!" << endl;
		} while (!validateSelection(row, col));

		do
		{
			cout << "Enter the row (1 to 4) and col (1 to 4) position of the pair: ";
			cin >> row >> col;
			cout << endl; //Line Break
			if (validateSelection(row, col))
				checkCard(row, col, SECOND_CHOICE, score);	//Second choice
			else
				cout << "Invalid selection! Please try again!" << endl;
		} while (!validateSelection(row, col));

	} while (score < 8);									//Continue loop until score is 8
	
	cout << "Press any key to Exit.";
	cin.ignore(2, '\n');
	cin.get(q);
	return 0;
}


void initializeCards()
{
	int cardDraw;

	for (int i = 0; i < 8; i++)
		deck::usedCard[i] = 0;

	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			do
			{
				cardDraw = rand() % 8 + 1;
				if (deck::usedCard[cardDraw] < 2)		//If card is used less then 2 times, continue
				{
					deck::table[row][col] = cardDraw;
					deck::usedCard[cardDraw]++;
					break;
				}
				else
					continue;
			} while (deck::usedCard[cardDraw] >= 2);	//If card drawn is used more than 2 times, loop until new card is drawn.
		}
	}
}

void initializePlaceholder()
{
	cout << setfill(' ');
	for (int row = 0; row < 4; row++)
	{
		for (int col = 0; col < 4; col++)
		{
			cout << right;
			cout << setw(4) << deck::placeholder[row][col];
		}
		cout << endl;	//Line Break
	}
}

bool validateSelection(char row, char col)
{
	for (int i = 0; i < 2; i++)
	{
		switch (row)		//Check if row is within range
		{
		case '1':
		case '2':
		case '3':
		case '4':
			swap(row, col);	//Swap row with col and recheck
			break;			//Continue
		default:
			cin.clear();	//Clear input stream
			return false;	//Return false if input is invalid
		}
	}
	return true;			//Return true if input is valid
}

char convertIntToChar(int number)
{
	//Converts integer to character
	return static_cast<char>(number + 48);
}

int convertCharToInt(char selection)
{
	//Converts character to integer
	return static_cast<int>(selection) - 48;
}

void checkCard(char row, char col, bool firstChoice, int& score)
{
	row = convertCharToInt(row);
	col = convertCharToInt(col);

	//Prevent a row/col from being picked if its already showing its value
	while (deck::placeholder[row - 1][col - 1] != '*' || !validateSelection(convertIntToChar(row), convertIntToChar(col)))
	{
		cout << (validateSelection(convertIntToChar(row), convertIntToChar(col)) 
			? "You already selected that card! Please try again!" 
			: "Invalid selection! Please try again!") << endl;
		cout << "Enter the row (1 to 4) and col (1 to 4) position of the pair: ";
		cin >> row >> col;
		row = convertCharToInt(row);
		col = convertCharToInt(col);
	}

	if (firstChoice)
	{
		//Display first pick
		deck::placeholder[row - 1][col - 1] = convertIntToChar(deck::table[row - 1][col - 1]); 
		initializePlaceholder();
		deck::firstCard = deck::table[row - 1][col - 1];				//set first card picked to firstCard
		deck::firstRow = row - 1;										//set first row picked to firstRow
		deck::firstCol = col - 1;										//set second row picked to secondRow
	}
	else
	{
		//Display second pick
		deck::placeholder[row - 1][col - 1] = convertIntToChar(deck::table[row - 1][col - 1]);
		if (deck::firstCard == deck::table[row - 1][col - 1])			//If first card picked = second card, match
		{
			initializePlaceholder();
			cout << "Pair match" << endl;
			initializePlaceholder();
			score++;													//Add to the score
		}
		else
		{
			initializePlaceholder();
			deck::placeholder[deck::firstRow][deck::firstCol] = '*';	//Reset first card back to '*'
			deck::placeholder[row - 1][col - 1] = '*';					//Reset second card back to '*'
			cout << "Pair do not match. Select again!" << endl;
			initializePlaceholder();
		}
		//Reset first card shown, first row picked, and first col picked
		deck::firstCard = 0;
		deck::firstRow = 0;
		deck::firstCol = 0;
	}
}

