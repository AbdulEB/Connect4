#pragma once
#include <vector>
#include "Board.h"
class gameplay //gameplay header class which will be the resource that will be 
{			// used across the other classes in the program
public:
	Board getBoard();
	bool getWinner();
	bool setWinner();
	int getBottomRow();
	int incBottomRow();
	int decBottomRow();
	std::vector<int> countChecker();
	int incCountChecker(int n);
	int decCountChecker(int n);
	void start();
	int getTurn();
	int incOrder();
	int decOrder();
	bool turn(int num);
	void pieceType();
	int playerTurn(int num);
	char getUserPiece();
	char getCPUPiece();
	gameplay();

};

