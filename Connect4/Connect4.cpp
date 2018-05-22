// Connect4.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Board.h"
#include <thread>
#include "Player1.h"
#include "Player2.h"
#include "gameplay.h"
#include <thread>
#include <iostream>
#include <vector>

using namespace std;


int main()
{
	gameplay g;// the game resources that wil be shared between both user and computer
	gameplay* gp; //threaded game resources
	gp = &g; // referencing the game resorce to threaded one
	Player1 p_1(gp);//initialize player 1
	Player2 p_2(gp);//initialize computer
	
	cout << &g << endl;

	cout << "Player's 1 piece is: " << gp->getUserPiece() << endl;
	cout << "Connie's piece is: " << gp->getCPUPiece() << endl;
	p_2.startThread();// start AI thread
	p_1.beginPlays();

	//declares winner
	if (gp->getTurn()==1)
		cout << "Player's 1 is the Winner" <<  endl;
	else cout << "Connie (Computer) is the Winner " << endl;

	return 0;
}
