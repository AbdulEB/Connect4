#include "stdafx.h"
#include "Board.h"
#include "iostream"
#include "Player1.h"
#include "Player2.h"
#include <vector>
#include <string>
#include "gameplay.h"


using namespace std;
int order = 0;
vector<int> counter;
Board b;
int bottomRow, count4=0;
bool Winner = false;
char cpuPiece,  userPiece;


//gets board from board class
Board gameplay::getBoard() {
	return b;
}
//used for the players while loop
bool gameplay::getWinner() {
	return Winner;
}
//once winner has been found it is set to true
bool gameplay::setWinner() {
	return Winner = true;
}
//get the value of the bottom row
int gameplay::getBottomRow() {
	return bottomRow;
}
//increase the bottom row value
int gameplay::incBottomRow() {
	return bottomRow++;
}
//decreases the bottom row value
int gameplay::decBottomRow() {
	return bottomRow--;
}
//gets counter
vector<int> gameplay::countChecker() {
	return counter;
}
//increases the counter based on column (used to assist in placing pieces)
int gameplay::incCountChecker(int n) {
	return counter.at(n)++;
}
//decreases the counter based on column (used to assist in placing pieces)
int gameplay::decCountChecker(int n) {
	return counter.at(n)--;
}
//starts the game, method called in the main class
void gameplay::start() {
	while (order < 1 || order>2) {
		cout << "Please enter 1 to go first or enter 2 for second:" << endl;
		cin >> order;
	}
	for (int i = 0; i < 8; i++) {
		counter.push_back(0);
	}
	
	b.buildBoard();
	b.printBoard();
	pieceType();
	bottomRow = 0;
}
//checks whose turn is it
int gameplay::getTurn() {
	return order;
}
//passes the turn from user to AI
int gameplay::incOrder() {
	return order++;
}
//passes turn from AI to user
int gameplay::decOrder() {
	return order--;
}
//asks user what piece he wants
void gameplay::pieceType() {
	int choose = 0;
	while (choose < 1 || choose>2) {
		cout << "Please enter 1 for X piece or enter 2 for O:" << endl;
		cin >> choose;
	}
	if (choose == 1) {
		userPiece = 'X';
		cpuPiece = 'O';
	}
	else {
		userPiece = 'O';
		cpuPiece = 'X';
	}

}
//returns user piece
char gameplay::getUserPiece() {
	return userPiece;
}
//returns the AI piece
char gameplay::getCPUPiece() {
	return cpuPiece;
}

//constructor
gameplay::gameplay() {
	


}