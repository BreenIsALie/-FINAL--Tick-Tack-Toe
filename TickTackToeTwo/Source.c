/*Tick Tack Toe game, made in C using an Array as the game board
Mathias J�nsson Oct 2014*/


/*### BUG TRACKER ###*

[Structural] Change win checking code from wall of if statements to loops
[Structural] PC related variables are the only ones not using a struct. Possibly change that (remember to change it across the code)

[Visual Improvement] Display final bord with Win message

[Code Cleanup] Get rid of warning message during compile
#####################
*/

#include <stdio.h>
#include <stdlib.h>

#define BOARDSIZE 3

/*FUNCTION DECLARATION*/
int RowSelection();
int ColumnSelection();
int CheckBoardFull(int *Board[BOARDSIZE][BOARDSIZE]);

/*PLAYER RELATED STRUCT AND VARIABLE DECLARATION*/
struct PlayerVariables				/*Struct containing player related variables*/
{
	int Row;						/*Which row (0-2) the player wants to place his marker in*/
	int Column;						/*Which column (0-2) the player wants to place his marker in*/
	int PlayerMenuChoice;			/*Used for the menu choices, To play again or exit*/
	int PlayerWeapon;				/*Contains the player weapon choice (X or O)*/
	int ChoiceUnique;				/*Checks if the players slot choice is free. Standard 1 for free, 0 for full*/
};

struct ForLoopVariables				/*Variables related to array for loops. Counters to go through and display in 3x3 grid */
{
	int Counter1;
	int Counter2;
};

struct GameControlVariables			/*Variables related to control of the game itself, such as the Winner int (Goes to 1 if winner is found) and the turn (run) counter*/
{
	int RunCount;					/*Turn counter. Ticks up 1 for each run of the while loop. Used to stop the game when the board is filled*/
	int PCRunCount;
	int BoardFilled;
};

int main(void)
{
	/*CONTAINS ALL THE PLAYER RELATED VARIABLES*/
	struct PlayerVariables PVariables;
	PVariables.PlayerMenuChoice = 0;												/*Stores the choice the player makes once the game is over (Play again or exit)*/
	PVariables.PlayerWeapon = 1;													/*Player Weapon (Marker)*/
	PVariables.ChoiceUnique = 0;													/*Used to check if the slot choice the player makes is free and valid. 1 for valid, 0 for invalid*/

	/*CONTAINS WIN CONDITION CHECKING AND BOARD PRINT VARIABLES*/
	struct ForLoopVariables WinVariables;
	WinVariables.Counter1 = 0;														/*Counters used in FOR loop to display the array*/
	WinVariables.Counter2 = 0;														/*Counters used in FOR loop to display the array*/

	/*CONTAINS GAME CONTROL RELATED VARIABLES*/
	struct GameControlVariables GameControl;
	int RunCount = 0;																/*Counts the number of rounds in the game, keeps it from running for longer then it takes to fill the board*/
	int PCRunCount;
	int BoardFilled = 0;

	/*CONTAINRS PC AI RELATED VARIABLES*/
	int PCRow;																		/*PC row selection*/
	int PCColumn;																	/*PC column selection*/
	int PCChoiceUnique = 0;															/*Check if PC slot selection is unique*/

	/*RANDOMIZER RELATED VARIABLES*/
	unsigned Seed;
	Seed = (unsigned)time(NULL);													/*RNG for computer opponents selections*/
	srand(Seed);																	/*Randomize using the unnasigned seed*/

	/*START OF MAIN PROGRAM LOOP. CONTROLS WHEN TO CLOSE OR RE-RUN THE PROGRAM*/
	while (PVariables.PlayerMenuChoice != 2)										/*Run until explicit exit conditions are met (Player decides to exit using PlayerMenuChoice)*/
	{
		int Board[BOARDSIZE][BOARDSIZE] = { 0 };									/*Create game board, 3x3 square, normal state being 0, player selected being 1 and PC selection being 2*/
		printf("\n { Welcome to Tick Tack Toe }\n");
		GameControl.RunCount = 1;													/*Set RunCount to 0, and reset RunCount to 0 after each game, so that the game doesn't immidiatly end*/

		/*START OF TURN LOOP. ACTUAL GAME RUNS HERE*/
		while (GameControl.RunCount <= 5 || BoardFilled != 1)											/*One run of this loop is one 'turn', run until someone has won or the board is filled*/
		{
			PCChoiceUnique = 0;														/*Reset the PC unique test between turns*/
			PVariables.ChoiceUnique = 0;											/*Reset the player unique test between turns*/

			/*BOARD DISPLAY USING FOR LOOP*/
			printf("\nCurrent Board:\n");
			for (WinVariables.Counter1 = 0; WinVariables.Counter1 < BOARDSIZE; WinVariables.Counter1++)					/*Print board using BOARDSIZE (= 3)*/
			{
				for (WinVariables.Counter2 = 0; WinVariables.Counter2 < BOARDSIZE; WinVariables.Counter2++)				/*Runs every 3 rounds to make the print "step down"*/
				{
					if (Board[WinVariables.Counter1][WinVariables.Counter2] == 0)
					{
						printf("| |");
					}
					else if (Board[WinVariables.Counter1][WinVariables.Counter2] == 1)
					{
						printf("|X|");
					}
					else if (Board[WinVariables.Counter1][WinVariables.Counter2] == 2)
					{
						printf("|O|");
					}
				}
				printf("\n");																							/*Make it step down each 3 rounds, creating the 3x3 square*/
			}

			/*PLAYER ROW / COLUMN SELECTION. DETERMINES WHERE PLAYERS MARK IS PLACED ON THE BOARD*/
			PVariables.Row = RowSelection();				/*Prompt the player to select a row, and place it into the Row variable (In PVariables struct)*/
			PVariables.Column = ColumnSelection();			/*Prompt the player to select a column, and place it into the Row variable (In PVariables struct)*/

			/*CHOICE VALIDATION SECTION. CHECKS THAT THE PLAYER HAS SELECTED AN EMPTY SLOT, RE-RUNS SELECTION IF THE SLOT WAS OCCUPIED*/
			while (PVariables.ChoiceUnique != 1)			/*Run the loop until the player has selected a valid, non occupied slot*/
			{

				if (Board[PVariables.Row][PVariables.Column] == 1 || Board[PVariables.Row][PVariables.Column] == 2)	/*Make the user enter new coordinates if the previous ones are taken*/
				{
					printf("\nERROR: Slot is already taken. Please select a new slot\n");
					PVariables.Row = RowSelection();
					PVariables.Column = ColumnSelection();
				}
				else if (Board[PVariables.Row][PVariables.Column] == 0)
				{
					Board[PVariables.Row][PVariables.Column] = PVariables.PlayerWeapon;
					PVariables.ChoiceUnique = 1;										/*Marks choice as valid and exits the loop*/
				}
			}

			GameControl.BoardFilled = CheckBoardFull(*Board);

			/*PC INPUT SECTION*/
			GameControl.PCRunCount = 0;
			while (PCChoiceUnique != 1 && GameControl.BoardFilled == 0)
			{

				int PCRow = (rand() % 3);												/*Set PC row choice to something between 1 and 3*/
				int PCColumn = (rand() % 3);											/*Set PC column choice to something between 1 and 3*/

				if (Board[PCRow][PCColumn] != 0)										/*Re-run the PC selection until a valid choice is taken*/
				{
					int PCRow = (rand() % 3);
					int PCColumn = (rand() % 3);
					GameControl.PCRunCount++;
				}
				else if (Board[PCRow][PCColumn] == 0)									/*If valid choice is taken, add marker to board and mark choice as valid, exit loop*/
				{
					Board[PCRow][PCColumn] = 2;
					PCChoiceUnique = 1;
				}
			}
			GameControl.BoardFilled = CheckBoardFull(*Board);
			/*COMPARISON / WINCHECK SECTION*/
			/*HORIZONTAL CHECK FOR BOTH PLAYER AND AI*/
			/*Checks if the Player has won on the horizontal lines (3 in a horizontal row)*/
			if (Board[0][0] == 1 && Board[0][1] == 1 && Board[0][2] == 1 || Board[1][0] == 1 && Board[1][1] == 1 && Board[1][2] == 1 || Board[2][0] == 1 && Board[2][1] == 1 && Board[2][2] == 1)
			{
				printf("\n\n\nCONGRATULATIONS. You have won\n\n\n");												/*Tell game a winner has been found, then exit loop*/
				break;
			}
			/*Check if the PC has won on horizontal lines*/
			if (Board[0][0] == 2 && Board[1][0] == 2 && Board[2][0] == 2 || Board[1][0] == 2 && Board[1][1] == 2 && Board[1][2] == 2 || Board[2][0] == 2 && Board[2][1] == 2 && Board[2][2] == 2)
			{
				printf("\n\n\nOH NO! The computer has won\n\n\n");												/*Tell game a winner has been found, then exit loop*/
				break;
			}
			/*VERTICAL CHECK FOR BOTH PLAYER AND AI*/
			/*Check if the player has won on vertical lines*/
			if (Board[0][0] == 1 && Board[1][0] == 1 && Board[2][0] == 1 || Board[0][1] == 1 && Board[1][1] == 1 && Board[2][1] == 1 || Board[0][2] == 1 && Board[1][2] == 1 && Board[2][2] == 1)
			{
				printf("\n\n\nCONGRATULATIONS. You have won\n\n\n");												/*Tell game a winner has been found, then exit loop*/
				break;
			}
			/*Check if the PC has won on vertical lines*/
			if (Board[0][0] == 2 && Board[1][0] == 2 && Board[2][0] == 2 || Board[0][1] == 2 && Board[1][1] == 2 && Board[2][1] == 2 || Board[0][2] == 2 && Board[1][2] == 2 && Board[2][2] == 2)
			{
				printf("\n\n\nOH NO! The computer has won\n\n\n");												/*Tell game a winner has been found, then exit loop*/
				break;
			}
			/*DIAGONAL CHECK FOR BOTH PLAYER AND AI*/
			/*Check if the player has won on diagonal lines*/
			if (Board[0][0] == 1 && Board[1][1] == 1 && Board[2][2] == 1 || Board[0][2] == 1 && Board[1][1] == 1 && Board[2][0] == 1)
			{
				printf("\n\n\nCONGRATULATIONS. You have won\n\n\n");												/*Tell game a winner has been found, then exit loop*/
				break;
			}
			/*Check if the PC has won on diagonal lines*/
			if (Board[0][0] == 2 && Board[1][1] == 2 && Board[2][2] == 2 || Board[0][2] == 2 && Board[1][1] == 2 && Board[2][0] == 2)
			{
				printf("\n\n\nOH NO! The computer has won\n\n\n");												/*Tell game a winner has been found, then exit loop*/
				break;
			}
			else
			{
				if (GameControl.BoardFilled == 1)
				{
					printf("\n\nDraw. You both loose\n\n");
					break;
				}
				else
				{
					GameControl.RunCount++;																			/*Make the turn counter tick up one step*/
				}

			}
		}
		/*POST-GAME MENY. EXIT OR PLAY AGAIN*/
		printf("Press 1 to play again\nPress 2 to exit ");
		scanf_s("%d", &PVariables.PlayerMenuChoice);
	}
	return 0;																			/*[Portal Turret voice]Goodbye[/Portal Turret voice]*/
}

/*FUNCTION TO LET THE PLAYER SELECT A ROW HERE*/
int RowSelection(void)
{
	int Pass = 0, Row = 0;																/*Row = The row the player wants. Pass = Checks if the number is valid (1-3)*/
	while (Pass != 1)																	/*While value representing valid choice isn't 1, run loop*/
	{
		printf("Select Row: ");
		scanf_s("%d", &Row);

		if (Row<1 || Row >3)															/*Check for valid row choice, display error if needed*/
		{
			printf("ERROR: Select valid row\n");
		}
		else
		{
			Pass = 1;																	/*Represents a valid row choice (1 is valid, anything else is not). Used to control the while loop*/
		}
	}
	return Row - 1;																		/*Adjust for array starting at 0 and then back to main*/
}

/*FUNCTION TO LET THE PLAYER SELECT A COLUMN HERE*/
int ColumnSelection(void)																/*Same as RowSeleciton, See it*/
{
	int Pass = 0, Column = 0;
	while (Pass != 1)																	/*Run as long as the choice isn't valid*/
	{
		printf("Select Column: ");
		scanf_s("%d", &Column);

		if (Column<1 || Column >3)														/*Print error message if the choice isn't 1 - 3 and make the player select again*/
		{
			printf("ERROR: Select valid Column\n");
		}
		else
		{
			Pass = 1;																	/*Set pass to 1, ending the loop if the choice is valid*/
		}
	}
	return Column - 1;																	/*Adjust for array starting at 0 and then back to main*/
}

/*FUNCTIONS TO CHECK IF THE BOARD IS FILLED*/
int CheckBoardFull(int *Board[BOARDSIZE][BOARDSIZE])
{
	/*Check if the board is filled. Break and declare tie if it is and no winner has been detected*/
	int CheckCounter1, CheckCounter2;

	for (CheckCounter1 = 0; CheckCounter1 < 3; CheckCounter1++)
	{
		for (CheckCounter2 = 0; CheckCounter2 < 3; CheckCounter2++)
		{
			if (Board[CheckCounter1][CheckCounter2] == 0)
			{
				return 0;
			}
			/*else if (Board[CheckCounter1][CheckCounter2] != 0)
			{
			printf("\n\nDraw. You both loose\n\n");
			return 1;
			}*/
		}
	}
	//printf("\n\nDraw. You both loose\n\n");
	return 1;
}

