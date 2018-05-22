#pragma once
#include <vector>
class Board
{
public: //header file for the board class to be includeds in other classes
	bool isWin(char c);
	void nearUser(int row, int column, char c, int t);
	void nearCPU(int row, int column, char c, int t);
	std::vector<int> valuePlace();
	int getUserValue(int row, int column);
	int getCPUValue(int row, int column);
	char getPiece(int row, int column);
	int getRowSize();
	std::vector<char> initialize();
	void placePiece(int row, int column, char c, int turns);
	void drop(char c, int tur);
	void printBoard();
	void buildBoard();
	Board();
};