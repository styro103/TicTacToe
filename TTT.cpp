//*********************************************************
//Shaun Mbateng
//This program is a game of Tic Tac Toe.
//Assuming All Correct Inputs, This Program Runs in O(N) Time
//*********************************************************

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// This function draws the board.
void drawboard(ostream &, char[], int8_t); // This Function Draws the Board.
int8_t humanmove(ostream & out, bool player, char board[], int8_t n); //This Function Handles the Human Move
int8_t compmove(ostream & out, int8_t diff, bool player, char board[], int8_t n); //This Function Handles the Computer Move
bool verticalwin(char board[], int8_t n, int8_t move); //Function That Checks for Vertical Win
bool horizontalwin(char board[], int8_t n, int8_t move); //Function That Checks for Horizontal Win
bool diagonalwin(char board[], int8_t n, int8_t move); //Function That Checks for Diagonal Win
bool draw(char board[], int8_t n); //Function That Checks for Draw Game
int8_t checkboard(char symbol, char board[], int8_t n); //Function for Computer to Check for Win or Loss
bool * checkmoves(char symbol, char board[],int8_t n); //Function to Check if Computer Move Will Allow Human to Win

int main () 
{
	int nop; //Number of Human Players
	int8_t diff; //Computer Difficulty Level, Will be 1, 2, or 3
	int8_t win = 0; //Whether Player has Won, or Quit, Will be 0, 1, or 2 When Returned
	bool player = 1; //Player Number, Initialized to Second Player
	bool first; //In 1 Human Player Game, Pick Who Goes First
	char board [9]; //Game Board, Only One Array
	ofstream outfile; //File to Print Results to
	
	outfile.open("GameLog.txt"); //Open GameLog
	
	//Menu of Game
	cout<<"Welcome to the Tic Tac Toe Game"<<endl;
	cout<<"Made by Shaun Mbateng\n"<<endl;
	cout<<"How many players will there be?"<<endl;
	
	//Loop Till Correct Input for Number of Players
	do
	{
		cout<<"Enter 0, 1, or 2: ";
		cin>>nop;
		/*
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
    	cin.clear(); //clear bad input flag
		*/
	}
	while (nop<0 || nop>2);
	
	if (nop<2) //If at Least One Computer Player
	{
		srand(time(NULL));	//Will Need Random Number Generator
		int btmp; //Temp Variable to Handle Human Error in Inputs
		cout<<"\nWhat is the difficulty level of the computer(s)?"<<endl;
		
		do //Loop Till Correct Input for Difficulty Level
		{
			cout<<"1=Easy, 2=Medium, 3=Hard: ";
			cin>>btmp;
			/*
			cin.ignore(numeric_limits<streamsize>::max(), '\n'); //discard input
    		cin.clear(); //clear bad input flag
			*/
		}
		while (btmp<1 || btmp>3);
		
		diff = btmp; //Set Difficulty Level
		
		if (nop==1) //One Human, One Computer
		{
			int ltmp; //Temp Variable to Handle Human Error in Inputs
			cout<<"\nDo you want to go first?"<<endl;
			
			do
			{
				cout<<"Enter 0 for no, 1 for yes: ";
				cin>>ltmp;
			}
			while (ltmp<0 || ltmp>1);
			
			first = ltmp; //Pick who Goes First
		}
	}
	
	for (int8_t i=0; i<9; i++) //Draw Board, Initialize With Corresponding Number
		board[i] = (i+1)+'0';
	
	//Display Start Messages
	cout<<"\n*** Game Start! ***"<<endl;
	outfile<<"*** Game Start! ***"<<endl;
	
	while (win==0) //While Game Unfinished
	{
		drawboard(cout, board, 9); //Draw Board on Screen
		drawboard(outfile, board, 9); //Draw Board on File
		player ^= 1; //XOR With 1, Switch Player from 0 to 1, or Vice Versa, Game Will Start at First Player
		
		//Call Move Function Depending on Number of Human Players
		switch (nop)
		{
			case 0: //No Humans
				win = compmove(outfile, diff, player, board, 9); //Check for Win
				break;
			case 1: //One Human
				if (player==first) //Booleans Match, Computer's Turn
					win = compmove(outfile, diff, player, board, 9); //Check for Win
				else //Boolean's Don't Match, Human's Turn
					win = humanmove(outfile, player, board, 9); //Check for Win
				break;
			case 2: //Both Human
				win = humanmove(outfile, player, board, 9); //Check for Win
				break;
			default: //Shouldn't Happen, but Just in Case
				win = -1;
				break;
		}
	}
	
	//Print Board Last Time
	drawboard(cout, board, 9);
	drawboard(outfile, board, 9);
	
	//Display Message Depending on Game Result
	switch (win)
	{
		case -1: //Player Chose to Quit
			cout<<"\nGame Quit\n"<<endl;
			outfile<<"\nGame Quit\n"<<endl;
			break;
		case 1: //Game was Won
			cout<<"\nPlayer "<<(player+1)<<" wins!"<<endl;
			outfile<<"\nPlayer "<<(player+1)<<" wins!"<<endl;
			break;
		case 2: //Draw Game
			cout<<"\nDraw Game."<<endl;
			outfile<<"\nDraw Game."<<endl;
			break;
		default: //Shouldn't Happen, but Just in Case
			break;
	}
	
	outfile.close(); //Close File
	
	return 0;
}

// This function prints the board to the indicated ostream object.
// The values in the board are 'X' for player 1, 'O' (the letter) for player 2, and 
// the corresponding number for an empty space.
void drawboard(ostream & out, char b[9], int8_t n) 
{
	out<<endl; //New Line
		
	for (int8_t i=0; i<n; i++)  //Output Game Board
	{	
		out<<"[ "<<b[i]<<" ]";
		
		if ((i+1)%3==0) //In Rows of 3
			out<<endl;
	}	
	
	out<<endl;
} // end drawboard function

int8_t humanmove(ostream & out, bool player, char board[9], int8_t n) //This Function Handles the Human Move
{
	int move; //Playing Move
	char symbol; //Playing Symbol
	
	if (player== 0) //First Player is X
		symbol = 'X';
	else //Second is O
		symbol = 'O';
		
	cout<<"What space does player "<<(player+1)<<" want to play?"<<endl; //Ask for Space
	
	do //Loop Till Valid Input
	{
		cout<<"(1-9, or 0 to Quit)"<<endl;
		cin>>move;
	}
	while (move<0 || move>9);
	
	if (move==0) //Return If Player Chose to Quit
		return -1;
	
	move -= 1; //To Adjust for Zero-Indexing
	
	if (board[move]<'1' || board[move]>'9') //Display if Row is Filled, Select Again
	{
		cout<<"\nThat space is filled.\n"<<endl;
		return humanmove(out, player, board, n); //Call Function Again
	}
	
	board[move] = symbol; //Play Piece
	cout<<"\nPlayer "<<(player+1)<<" plays in space "<<(move+1)<<endl; //Display Play Message
	out<<"Player "<<(player+1)<<" plays in space "<<(move+1)<<endl; //Outfile Play Message
	
	if //Check for Game Win
	(
		verticalwin(board, n, move) || 
		horizontalwin(board, n, move) || 
		diagonalwin(board, n, move)
	)
		return 1;
	if (draw(board, n)) //Check for Draw Game
		return 2;
	
	return 0; //Return 0 on Default
}

int8_t compmove(ostream & out, int8_t diff, bool player, char board[], int8_t n) //This Function Handles the Computer Move
{
	int8_t move = -1; //Playing Column, Initialized to -1
	bool * moves; //Pointer to Hold Potential Computer Loss Columns
	char symbol; //Playing Symbol
	
	if (player== 0) //First Player is X
		symbol = 'X';
	else //Second is O
		symbol = 'O';
	
	if (diff>1) //Difficulty Level is More Than 1
	{
		//if (diff==3) //Max Difficulty
			//move = 3; //Play Center Column If Bottom Space Open, Necessary to Assure Victory
		if (move==-1) //Space Already Filled
			move = checkboard(symbol, board, n); //Check If Computer can Win
		if (move==-1) //No Winning Move for Computer
		{
			char tmp = 'X'; //Temporary Variable for Symbol
			
			if (player==0) //Set to Opposite Player Symbol
				tmp = 'O';
				
			move = checkboard(tmp, board, n); //Check If Human can Win
		}
		if (move==-1 && diff==3) //Max Difficulty, Move Not Decided Yet
		{
			moves = checkmoves(symbol, board, n); //Check If Any Move Will Setup Human Win
			
			do //Choose Random Number, but Make Sure it Won't Result in Human Win
				move=rand()%9;
			while ((board[move]<'1' || board[move]>'9') || moves[move]==1);
		}
	}
	if (move==-1)
	{
		//Create Random Number from 0-6, Loop Till Acceptable Input
		do
			move=rand()%9;
		while (board[move]<'1' || board[move]>'9');
	}
	
	board[move] = symbol; //Play Piece
	cout<<"\nComputer Player "<<(player+1)<<" plays in space "<<(move+1)<<endl; //Display Play Message
	out<<"Computer Player "<<(player+1)<<" plays in space "<<(move+1)<<endl; //Outfile Play Message
	
	if //Check for Game Win
	(
		verticalwin(board, n, move) || 
		horizontalwin(board, n, move) || 
		diagonalwin(board, n, move)
	)
		return 1;
	if (draw(board, n)) //Check for Draw Game
		return 2;
	
	return 0;
}

bool verticalwin(char board[], int8_t n, int8_t move) //Function That Checks for Vertical Win
{	
	switch (move) //Check Different Areas Based on Move
	{	
		case 0:
		case 1:
		case 2:
			if (board[move]==board[move+3] && board[move]==board[move+6]) //Top Row Checks Spaces Under in Respective Column
				return true;
			break;
		case 3:
		case 4:
		case 5:
			if (board[move]==board[move-3] && board[move]==board[move+3]) //Middle Row Checks Space Above and Under in Respective Column
				return true;
			break;
		case 6:
		case 7:
		case 8:
			if (board[move]==board[move-3] && board[move]==board[move-6]) //Bottom Row Checks Spaces Above in Respective Column
				return true;
			break;
		default: //Shouldn't Happen, but Just in Case
			break;
	}
	
	return false; //Return False on Default
}

bool horizontalwin(char board[], int8_t n, int8_t move) //Function That Checks for Horizontal Win
{
	switch (move) //Check Different Areas Based on Move
	{	
		case 0:
		case 3:
		case 6:
			if (board[move]==board[move+1] && board[move]==board[move+2]) //Left Column Checks Spaces Right in Respective Row
				return true;
			break;
		case 1:
		case 4:
		case 7:
			if (board[move]==board[move-1] && board[move]==board[move+1]) //Middle Column Checks Space Left and Right in Respective Row
				return true;
			break;
		case 2:
		case 5:
		case 8:
			if (board[move]==board[move-1] && board[move]==board[move-2]) //Right Column Checks Spaces Left in Respective Row
				return true;
			break;
		default: //Shouldn't Happen, but Just in Case
			break;
	}
	
	return false; //Return False on Default
}

bool diagonalwin(char board[], int8_t n, int8_t move) //Function That Checks for Diagonal Win
{
	switch (move) //Check Different Areas Based on Move
	{
		case 4: //Move at Center
		case 0: //Move at Up-Left
		case 8: //Move at Down-Right
			if (board[0]==board[4] && board[4]==board[8]) //Check Down-Right
				return true;
			if (move==0 || move==8) //No Need for Checking Other Diagonal
				break;
		case 2: //Move at Up-Right
		case 6: //Move at Down-Left
			if (board[2]==board[4] && board[4]==board[6]) //Check Down-Left
				return true;
			break;
		default: //On Space That Can't Result in Diagonal Win
			break;
	}
	
	return false; //Return False on Default
}

bool draw(char board[], int8_t n) //Function That Checks for Draw Game
{
	for (int8_t i=0; i<n; i++) //Loop Through Board
	{
		if (board[i]>='1' && board[i]<='9') //Return If Any Open Space Found
			return false;
	}
	
	return true; //If Not, Return False
}

int8_t checkboard(char symbol, char board[], int8_t n) //Function for Computer to Check for Win or Loss
{
	return -1;
}
bool * checkmoves(char symbol, char board[], int8_t n) //Function to Check if Computer Move Will Allow Human to Win
{
	static bool moves[9]; //Keep Track of Columns
	
	return moves;
}
