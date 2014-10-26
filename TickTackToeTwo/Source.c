/*Tick Tack Toe game, made in C using an Array as the game board
Mathias Jönsson Oct 2014*/


/*### BUG TRACKER ###*

#Game does not add to board after first add for both players (probably loop)

*/

#include <stdio.h>
#include <stdlib.h>

#define BOARDSIZE 3

/*FUNCTION DECLARATION*/
int XOSelection();
int RowSelection();
int ColumnSelection();
int CheckWinner();

/*PLAYER RELATED STRUCT AND VARIABLE DECLARATION*/
struct PlayerVariables										/*Struct containing player related variables*/	
{
	int Row;												/*Which row (0-2) the player wants to place his marker in*/
	int Column;												/*Which column (0-2) the player wants to place his marker in*/
	int PlayerMenuChoice;									/*Used for the menu choices, To play again or exit*/
	int PlayerWeapon;										/*Contains the player weapon choice (X or O)*/
	int ChoiceUnique;
};

struct WinCheckVariables
{
	int Counter1;
	int Counter2;
	int Sum;
};

struct GameControlVariables
{
	int RunCount;
	int Winner;
};

int main(void)
{
	/*CONTAINS ALL THE PLAYER RELATED VARIABLES*/
	struct PlayerVariables PVariables;
	PVariables.PlayerMenuChoice = 0;
	PVariables.PlayerWeapon = 0;
	PVariables.ChoiceUnique = 0;

	/*CONTAINS WIN CONDITION CHECKING AND BOARD PRINT VARIABLES*/
	struct WinCheckVariables WinVariables;
	WinVariables.Counter1 = 0;
	WinVariables.Counter2 = 0;
	WinVariables.Counter1 = 0;
	WinVariables.Sum = 0;

	/*CONTAINS GAME CONTROL RELATED VARIABLES*/
	struct GameControlVariables GameControl;
	int Winner = 0;																	/*Used by the CheckWinner() function, this marks if a winner is found or not. Used to end the while loop*/
	int RunCount = 0;																/*Counts the number of rounds in the game, keeps it from running for longer then it takes to fill the board*/

	/*CONTAINRS PC AI RELATED VARIABLES*/
	unsigned Seed;
	Seed = (unsigned)time(NULL);													/*RNG for computer opponents selections*/
	srand(Seed);
	int PCRow;
	int PCColumn;
	int PCChoiceUnique = 0;															/*Check if PC slot selection is unique*/

	/*START OF MAIN PROGRAM LOOP. CONTROLS WHEN TO CLOSE OR RE-RUN THE PROGRAM*/
	while (PVariables.PlayerMenuChoice != 2)										/*Run until explicit exit conditions are met (Player decides to exit)*/
	{ 
		int Board[BOARDSIZE][BOARDSIZE] = { 0 };									/*Create game board, 3x3 square*/
		PVariables.PlayerWeapon = XOSelection();
		GameControl.RunCount = 0;
		GameControl.Winner = 0;

		/*START OF TURN LOOP. ACTUAL GAME RUNS HERE*/
		while (GameControl.Winner == 0 || GameControl.RunCount <= 3)											/*One run of this loop is one 'turn'*/
		{
			PCChoiceUnique = 0;
			PVariables.ChoiceUnique = 0;

			/*PLAYER WEAPON SELECTION AND BOARD DISPLAY*/
			
			printf("\nCurrent Board:\n");
			for (WinVariables.Counter1 = 0; WinVariables.Counter1 < BOARDSIZE; WinVariables.Counter1++)					/*Print board*/
			{
				for (WinVariables.Counter2 = 0; WinVariables.Counter2 < BOARDSIZE; WinVariables.Counter2++)				/*Runs every 3 rounds to make the print "step down"*/
				{
					printf(" %d ", Board[WinVariables.Counter1][WinVariables.Counter2]);
				}
				printf("\n");																							/*Make it step down each 3 rounds, creating the 3x3 square*/
			}

			/*PLAYER ROW / COLUMN SELECTION. DETERMINES WHERE PLAYERS MARK IS PLACED ON THE BOARD*/
			PVariables.Row = RowSelection();
			PVariables.Column = ColumnSelection();

			/*CHOICE VALIDATION SECTION. CHECKS THAT THE PLAYER HAS SELECTED AN EMPTY SLOT, RE-RUNS SELECTION IF THE SLOT WAS OCCUPIED*/
			while (PVariables.ChoiceUnique != 1)
			{

				if (Board[PVariables.Row][PVariables.Column] == 1 || Board[PVariables.Row][PVariables.Column] == 2)
				{
					printf("ERROR: Slot is already taken. Please select a new slot");
					PVariables.Row = RowSelection;
					PVariables.Column = ColumnSelection;
				}
				else if (Board[PVariables.Row][PVariables.Column] == 0)
				{
					Board[PVariables.Row][PVariables.Column] = 1;
					PVariables.ChoiceUnique = 1;
				}
			}

			/*PC INPUT SECTION*/
			while (PCChoiceUnique != 1)
			{
				int PCRow = (rand() % 3);												/*Set PC row choice to something between 1 and 3*/
				int PCColumn = (rand() % 3);											/*Set PC column choice to something between 1 and 3*/

				if (Board[PCRow][PCColumn] != 0)
				{
					int PCRow = (rand() % 3);
					int PCColumn = (rand() % 3);
				}
				else if (Board[PCRow][PCColumn] == 0)
				{
					Board[PCRow][PCColumn] = 2;
					PCChoiceUnique = 1;
				}
			}
			/*COMPARISON / WINCHECK SECTION*/
			/*HORIZONTAL CHECK FOR BOTH PLAYER AND AI*/
			if (Board[0][0] == 1 && Board[0][1] == 1 && Board[0][2] == 1 || Board[1][0] == 1 && Board[1][0] == 1 && Board[1][0] == 1 || Board[2][0] == 1 && Board[2][0] == 1 && Board[2][0] == 1)
			{
				printf("\n\n\nCONGRATULATIONS. You have won\n\n");
				GameControl.Winner = 1;
				break;
			}
			if (Board[0][0] == 2 && Board[1][0] == 2 && Board[2][0] == 2 || Board[1][0] == 2 && Board[1][1] == 2 && Board[1][2] == 2 || Board[2][0] == 2 && Board[2][1] == 2 && Board[2][2] == 2)
			{
				printf("\n\n\nOH NO! The computer has won\n\n");
				GameControl.Winner = 1;
				break;
			}
			/*VERTICAL CHECK FOR BOTH PLAYER AND AI*/
			if (Board[0][0] == 1 && Board[1][0] == 1 && Board[2][0] == 1 || Board[0][1] == 1 && Board[1][1] == 1 && Board[2][1] == 1 || Board[0][2] == 1 && Board[1][2] == 1 && Board[2][2] == 1)
			{
				printf("\n\n\nCONGRATULATIONS. You have won\n\n");
				GameControl.Winner = 1;
				break;
			}
			if (Board[0][0] == 2 && Board[1][0] == 2 && Board[2][0] == 2 || Board[0][1] == 2 && Board[1][1] == 2 && Board[2][1] == 2 || Board[0][2] == 2 && Board[1][2] == 2 && Board[2][2] == 2)
			{
				printf("\n\n\nOH NO! The computer has won\n\n");
				GameControl.Winner = 1;
				break;
			}
			/*DIAGONAL CHECK FOR BOTH PLAYER AND AI*/
			if (Board[0][0] == 1 && Board[1][1] == 1 && Board[2][2] == 1 || Board[0][2] == 1 && Board[1][1] == 1 && Board[2][0] == 1)
			{
				printf("\n\n\nCONGRATULATIONS. You have won\n\n");
				GameControl.Winner = 1;
				break;
			}
			if (Board[0][0] == 2 && Board[1][1] == 2 && Board[2][2] == 2 || Board[0][2] == 2 && Board[1][1] == 2 && Board[2][0] == 2)
			{
				printf("\n\n\nOH NO! The computer has won\n\n");
				GameControl.Winner = 1;
				break;
			}
			else
			{
				GameControl.RunCount++;
				GameControl.Winner = 0;
			}
		}
		printf("\n\n\nWhat do you want do do now?\n");
		printf("Press 1 to play again\nPress 2 to exit ");
		scanf_s("%d", &PVariables.PlayerMenuChoice);
	}
	return 0;
}

int XOSelection(void)																/*Player selects to play as X or O*/
{
	int PlayerWeapon;
	printf("\nWhat do you want to play as ? \nX = 1, O = 2\n");
	scanf_s("%d", &PlayerWeapon);

	while (PlayerWeapon != 1 || PlayerWeapon != 2)									/*Run while valid weapon isn't selected*/
	{
		if (PlayerWeapon == 1 || PlayerWeapon == 2)									/*Break and return value when valid is entered*/
		{
			break;
		}
		else
		{
			printf("ERROR: Select valid choice\n");									/*Return error as normal if the value isn't allowed*/
			scanf_s("%d", &PlayerWeapon);
		}
	}
	return PlayerWeapon;															/*Back to main we go*/
}

int RowSelection(void)
{
	int Pass = 0, Row = 0;
	while (Pass != 1)									/*While value representing valid choice isn't 1, run loop*/
	{
		printf("Select Row: ");
		scanf_s("%d", &Row);

		if (Row<1 || Row >3)							/*Check for valid row choice, display error if needed*/
		{
			printf("ERROR: Select valid row");
		}
		else
		{
			Pass = 1;									/*Represents a valid row choice (1 is valid, anything else is not). Used to control the while loop*/
		}
	}
	return Row - 1;										/*Adjust for array starting at 0 and then back to main*/
}

int ColumnSelection(void)								/*Same as RowSeleciton, See it*/
{
	int Pass = 0, Column = 0;
	while (Pass != 1)
	{
		printf("Select Column: ");
		scanf_s("%d", &Column);

		if (Column<1 || Column >3)
		{
			printf("ERROR: Select valid Column");
		}
		else
		{
			Pass = 1;
		}
	}
	return Column - 1;									/*Adjust for array starting at 0 and then back to main*/
}


