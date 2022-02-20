
// Group 4 Minesweeper

// ----------------------------------------------


// Objective of the game:

// The game ends when the player probes a cell containing a mine. The objective of the game is to uncover every square that does not contain a mine. 
// Player should finish the game without denoting any bomb.


// ----------------------------------------------


// Overview of the game:

// Minesweeper is a single-player puzzle game. At the start of a game, the player receives an n × m rectangular grid of covered squares or cells. 
// Each turn, the player may probe or uncover a square revealing either a mine or an integer. This integer represents the number of mines adjacent to that square. 
// There are three difficulty levels for Minesweeper: beginner, intermediate, and expert. Beginner has a total of ten mines and the board size is either 8 × 8, 9 × 9, or 10 × 10,
// Intermediate has 40 mines and also varies in size between 13 × 15 and 16 × 16. Finally, expert has 99 mines and is always 16 × 30 (or 30 × 16).  As the difficulty increases, guessing becomes
// more common with expert configurations having numerous instances of guessing. Furthermore, higher numbered cells are more prevalent. 
// But we've made changes about the game wherein the player will decide his/her prefer board size and number of mines.


// ----------------------------------------------


// Instructions: 

// You are presented with a board of squares( asterisk ). Some squares (asterisk) contain mines (bombs), others don't. 
// If you click on a square (asterisk) containing a bomb, you lose. If you manage to click all the squares without clicking on any bombs you win.
// Clicking a square which doesn't have a bomb reveals the number of neighboring squares containing bombs. Use this information plus some guess work to avoid the bombs.


// -----------------------------------------------


// Code

#include <bits/stdc++.h> // Basically a header than includes everything

using namespace std;

// Creating constants and their max possible values
#define MAXSIDE 25
#define MAXMINES 99

// Function declarations
void SIDEMINES();
bool isValid(int, int);
bool isMine(int, int);
void printBoard(char);
void replaceMine(int, int, char);
int countAdjacentMines(int, int, int);
bool playMinesweeperUtil(char, char);
void placeMines(int, char);
void initialise(char, char);
void playMinesweeper();
void makeMove(int, int);

int SIDE; // side length of the board
int MINES; // number of mines on the board




// Main function
int main()
{
	// Asking the user to input preferred board size and amount of mimes
    SIDEMINES();

	playMinesweeper ();

	return (0);
}




// Function to ask user their preferred board size and amount of mines
void SIDEMINES()
{
	cout << "Input size of board (9-25): ";
    cin >> SIDE;
    cout << "input amount of Mines (max 99): ";
    cin >> MINES;
    
    return;
}

// Function for user to input their move
void makeMove(int *x, int *y)
{
	printf("Enter your move in this format: (row column): ");
	scanf("%d %d", x, y);
	
	return;
}

// Function to check if input is a valid cell or not
bool isValid(int row, int col)
{
	// Returns true if input is valid
	return (row >= 0) && (row < SIDE) &&
	(col >= 0) && (col < SIDE);
}

// Function to check if cell has a mine
bool isMine (int row, int col, char board[][MAXSIDE])
{
	if (board[row][col] == '*')
		return (true);
	else
		return (false);
}

// Function to print the game board
void printBoard(char myBoard[][MAXSIDE])
{
	int i, j;

	printf ("  ");

	for (i=0; i<SIDE; i++)
		printf ("%d ", i);

	printf ("\n");

	for (i=0; i<SIDE; i++)
	{
		printf ("%d ", i);

		for (j=0; j<SIDE; j++)
			printf ("%c ", myBoard[i][j]);
		printf ("\n");
	}
	
	return;
}

// Function to replace the mines with a blank space
void replaceMine (int row, int col, char board[][MAXSIDE])
{
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
			{
				if (board[i][j] != '*')
				{
					board[i][j] = '*';
					board[row][col] = '-';
					return;
				}
			}
	}
	
	return;
}

// A Function to count the number of mines in the nearby cells
int countAdjacentMines(int row, int col, int mines[][2], 
	char realBoard[][MAXSIDE])
{

	int i;
	int count = 0;

	// North tile

		if (isValid (row-1, col) == true)
		{
			if (isMine (row-1, col, realBoard) == true)
			count++;
		}

	// South tile

		if (isValid (row+1, col) == true)
		{
			if (isMine (row+1, col, realBoard) == true)
			count++;
		}

	// East tile

		if (isValid (row, col+1) == true)
		{
			if (isMine (row, col+1, realBoard) == true)
			count++;
		}

	// West tile

		if (isValid (row, col-1) == true)
		{
			if (isMine (row, col-1, realBoard) == true)
			count++;
		}

	// North-east tile

		if (isValid (row-1, col+1) == true)
		{
			if (isMine (row-1, col+1, realBoard) == true)
			count++;
		}

	// North-west tile

		if (isValid (row-1, col-1) == true)
		{
			if (isMine (row-1, col-1, realBoard) == true)
			count++;
		}

	// South-east tile

		if (isValid (row+1, col+1) == true)
		{
			if (isMine (row+1, col+1, realBoard) == true)
			count++;
		}

	// South-west tile

		if (isValid (row+1, col-1) == true)
		{
			if (isMine (row+1, col-1, realBoard) == true)
			count++;
		}

	return (count);
}

// Function to play Minesweeper
bool playMinesweeperUtil(char myBoard[][MAXSIDE], char realBoard[][MAXSIDE],
	int mines[][2], int row, int col, int *movesLeft)
{

	// Make sure the same board doesn't repeat itself
	if (myBoard[row][col] != '-')
		return (false);

	int i, j;

	// What happens when you find a mine
	if (realBoard[row][col] == '*')
	{
		myBoard[row][col]='*';

		for (i=0; i<MINES; i++)
			myBoard[mines[i][0]][mines[i][1]]='*';

		printBoard (myBoard);
		printf ("\nYOU LOSE\n");
		return (true) ;
	}

	else
	{
		int count = countAdjacentMines(row, col, mines, realBoard);
		(*movesLeft)--;

		myBoard[row][col] = count + '0';

		if (!count)
		{
			// North tile

			if (isValid (row-1, col) == true)
			{
				if (isMine (row-1, col, realBoard) == false)
				playMinesweeperUtil(myBoard, realBoard, mines, row-1, col, movesLeft);
			}

			// South tile

			if (isValid (row+1, col) == true)
			{
				if (isMine (row+1, col, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col, movesLeft);
			}

			// East tile

			if (isValid (row, col+1) == true)
			{
				if (isMine (row, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col+1, movesLeft);
			}

			// West tile

			if (isValid (row, col-1) == true)
			{
				if (isMine (row, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row, col-1, movesLeft);
			}

			// North-East tile

			if (isValid (row-1, col+1) == true)
			{
				if (isMine (row-1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col+1, movesLeft);
			}

			// North-west tile

			if (isValid (row-1, col-1) == true)
			{
				if (isMine (row-1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row-1, col-1, movesLeft);
			}

			// South-east tile

			if (isValid (row+1, col+1) == true)
			{
				if (isMine (row+1, col+1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col+1, movesLeft);
			}

			// South-west tile

			if (isValid (row+1, col-1) == true)
			{
				if (isMine (row+1, col-1, realBoard) == false)
					playMinesweeperUtil(myBoard, realBoard, mines, row+1, col-1, movesLeft);
			}
		}

		return (false);
	}
}

// A Function to place the mines randomly
void placeMines(int mines[][2], char realBoard[][MAXSIDE])
{
	bool mark[MAXSIDE*MAXSIDE];

	memset (mark, false, sizeof (mark));

	for (int i=0; i<MINES; )
	{
		int random = rand() % (SIDE*SIDE);
		int x = random / SIDE;
		int y = random % SIDE;

		if (mark[random] == false)
		{
			mines[i][0]= x;
			mines[i][1] = y;

			realBoard[mines[i][0]][mines[i][1]] = '*';
			mark[random] = true;
			i++;
		}
	}

	return;
}

// Function to start the game
void initialise(char realBoard[][MAXSIDE], char myBoard[][MAXSIDE])
{
	// Random number generator so the same board doesn't appear again 
	srand(time (NULL));
	
	for (int i=0; i<SIDE; i++)
	{
		for (int j=0; j<SIDE; j++)
		{
			myBoard[i][j] = realBoard[i][j] = '-';
		}
	}

	return;
}

// Function to play Minesweeper game
void playMinesweeper ()
{
	bool gameOver = false;
    char realBoard[MAXSIDE][MAXSIDE], myBoard[MAXSIDE][MAXSIDE];

	int movesLeft = SIDE * SIDE - MINES, x, y;
	int mines[MAXMINES][2];

	initialise (realBoard, myBoard);
	placeMines (mines, realBoard);

	int currentMoveIndex = 0;
	while (gameOver == false)
	{
		printf ("Current Status of Board : \n");
		printBoard (myBoard);
		makeMove (&x, &y);

		// TO make sure the first move is always a safe move
		if (currentMoveIndex == 0)
		{
			if (isMine (x, y, realBoard) == true)
				replaceMine (x, y, realBoard);
		}

		currentMoveIndex ++;

		gameOver = playMinesweeperUtil (myBoard, realBoard, mines, x, y, &movesLeft);

		if ((gameOver == false) && (movesLeft == 0))
		{
			printf ("\nYOU WIN!\n");
			gameOver = true;
		}
	}
	
	return;
}


