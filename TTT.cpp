//*********************************************************
//Shaun Mbateng
//This program is a game of Tic Tac Toe.
//*********************************************************

#include <iostream>
#include <fstream>
#include <stdint.h>
#include <stdlib.h>
#include <time.h>
using namespace std;

// This program is written by Ankur Gupta.
// This program is a template for the Connect Four game.

// This function draws the board.
void drawboard(ostream &, char [][3], int8_t); // This Function Draws the Board.

int main () 
{
	char board [3][3] = {0}; //Game Board
	
	for (int8_t x = 1; x <= 3; x++) //Draw Board, Initialize With "-"
	{
		int8_t y = 1;
		
		switch(y)
		{
			case 1:
				board[x-1][y-1] = (x*y)+2*(x-1)+'0';
				y++;
			case 2:
				board[x-1][y-1] = (x*y)+(x-1)+'0';
				y++;
			case 3:
				board[x-1][y-1] = (x*y)+'0';
		}
		/*for (int8_t y = 1; y <= 3; y++)
		{
			switch (y)
			board[x-1][y-1] = (x*y)+'0';
		}*/
	}
	
	drawboard(cout, board, 3); //Draw Board on Screen
	
	return 0;
}

// This function prints the board to the indicated ostream object.
// The values in the board are 'X' for player 1, 'O' (the letter) for player 2, and 
// the ASCII value of 0 (zero) for an empty space.
void drawboard(ostream & out, char b[][3], int8_t sq) 
{
	out << endl;
	
	//for (int8_t i=1; i<=sq; i++) //Display Column Numbers
		//out<<(int) i<<" "; //Display as Integers
		
	out<<"\n"<<endl;
		
	for (int8_t x = 0; x<sq; x++)  //Output Game Board
	{	
		for (int8_t y = 0; y < sq; y++)
			out<<"["<<b[x][y]<<"]";
		
		out<<endl;
	}	
	
	out << endl << endl;
} // end drawboard function
