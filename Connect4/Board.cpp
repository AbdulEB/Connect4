#include "stdafx.h"
#include "Board.h"
#include "iostream"
#include <vector>

using namespace std;
vector<vector<char>> board; //board 
vector<vector<int>> placeValueUser; // int array that marks valuable available places for the user
vector<vector<int>> placeValueCPU; // int array that marks valuable available places for the AI

//method to check if the game has won
bool Board::isWin(char c) {//passes the current game piece that went on to play
	bool result = false; // return variable
	//nested loop that BFS to check winner
	for (int i = 0; i < board.size(); i++) {
		for (int j = 0; j < board.at(i).size(); j++) {
			if (board[i][j] == c) { //check the game piece if present to run the following if statements
				//if statement to make sure it won't go beyone the board
				if (i <= 4) {
					//checks if it is a vetical win (|)
					if (board[i][j] == c && board[i+1][j] == c && board[i+2][j] == c && board[i+3][j] == c) {
						return result = true;
					}
					//checks if it is a diagonal downward win (\)
					else if (board[i][j] == c && board[i + 1][(j + 1) % 8] == c
						&& board[i + 2][(j + 2) % 8] == c && board[i + 3][(j + 3) % 8] == c) {
						return result = true;
					}					
				}
				//if statement to ensure it won't go beyond the board
				if (i >= 3) {
					//checks if it is a diagonal upward win (/)
					if (board[i][j] == c && board[i - 1][(j + 1) % 8] == c
						&& board[i - 2][(j + 2) % 8] == c && board[i - 3][(j + 3) % 8] == c) {
						return result = true;
					}
				}
				//checks if it is a horizontal win (-)
				if (board[i][j] == c && board[i][(j + 1) % 8] == c
					&& board[i][(j + 2) % 8] == c && board[i][(j + 3) % 8] == c) {
					return result = true;
				}
			}
		}
	}
	return result;
}
//method to increase the value of available spaces for the user, used in the AI decision making
void Board::nearUser(int row, int column, char c, int t) {
	int m = row - 1;
	int n = row + 1;
	if (m == -1) {
		m = 0;
	}
	if (n == 8) {
		n = 7;
	}
	for (int i = m; i <= n; i++) {
		for (int j = column - 1; j <= column + 1; j++) {
			int tempJ = j;
			if (j == -1) {
				j += 8;
			}
			else if (j == 8) {
				j -= 8;
			}
			if (i == row && j == column);
			else if (t == 1 && board[i][j] == c) {
				placeValueUser[row][column]= placeValueUser[row][column]+ placeValueUser[i][j];

			}
			j = tempJ;
		}
	}
}
//method to increase the value of available spaces for the cpu, used in the AI decision making
void Board::nearCPU(int row, int column, char c, int t) {
	int m = row - 1;
	int n = row + 1;
	if (m == -1) {
		m = 0;
	}
	if (n == 8) {
		n = 7;
	}
	for (int i = m; i <= n; i++) {
		for (int j = column - 1; j <= column + 1; j++) {
			int tempJ = j;
			if (j == -1) {
				j += 8;
			}
			else if (j == 8) {
				j -= 8;
			}
			if (i == row && j == column);
			else if (t == 2 && board[i][j] == c) {
				placeValueCPU[row][column]= placeValueCPU[row][column]+ placeValueCPU[i][j];

			}
			j = tempJ;
		}
	}
}
//initialize the empty value per row
vector<int> Board::valuePlace() {
	vector<int> blankRow;
	for (int i = 0; i<8; i++) {
		blankRow.push_back(0);
	}
	return blankRow;
}
//returns a user space value, used for the AI decision making
int Board::getUserValue(int row, int column) {
	return placeValueUser[row][column];
}
//returns a AI space value, used for the AI decision making
int Board::getCPUValue(int row, int column) {
	return placeValueCPU[row][column];
}

//get Piece char value
char Board::getPiece(int row, int column) {
	return board[row][column];
}
//get the row size else of the board
int Board::getRowSize() {
	return board.size();
}
//creats a new row
vector<char> Board::initialize() {
	vector<char> blankRow;
	for (int i = 0; i<8; i++) {
		blankRow.push_back(' ');
	}
	return blankRow;
}
//places a piece on the board
void Board::placePiece(int row, int column, char c, int turns) {
	board[row][column] = c;
	int m = row - 1;
	int n = row + 1;
	if (m == -1) {
		m = 0;
	}
	if (n == 8) {
		n = 7;
	}
	for (int i = m; i <= n; i++) {
		for (int j = column - 1; j <= column + 1; j++) {
			int tempJ = j;
			if (j == -1) {
				j += 8;
			}
			else if (j == 8) {
				j -= 8;
			}
			if (i == row && j == column);
			else if (turns == 1 && board[i][j]==' ') {
				placeValueUser.at(i).at(j)++;
				nearUser(i, j, c, turns);
			}
			else if (turns == 2 && board[i][j] == ' ') {
				placeValueCPU.at(i).at(j)++;
				nearCPU(i, j, c, turns);
			}
			j = tempJ;
		}
	}

}
//drops the last row if filled
void Board::drop(char c, int tur) {
	vector<int> xDelim, oDelim;
	//for loop to initialize the value arrays that will need the new bottom row values reduced
	for (int i = 0; i < 8; i++) {
		xDelim.push_back(0);
		oDelim.push_back(0);
	}
	for (int i = 0; i < 8; i++) {
		for (int j = i - 1; j <= i + 1; j++) {
			int tempJ = j;
			if (j == -1) {
				j += 8;
			}
			else if (j == 8) {
				j -= 8;
			}
			if (board.at(7).at(i) == 'X') {
				xDelim.at(j)++;
			}
			if (board.at(7).at(i) == 'O') {
				oDelim.at(j)++;
			}
			j = tempJ;
		}
		
	}
	//drops bottom rows and creat a new freash top rows
	board.pop_back();
	board.insert(board.begin(), initialize());
	placeValueUser.pop_back();
	placeValueUser.insert(placeValueUser.begin(), valuePlace());
	placeValueCPU.pop_back();
	placeValueCPU.insert(placeValueCPU.begin(), valuePlace());
	//reduces the values of the bottom spaces
	for (int i = 0; i < 8; i++) {
		if (tur == 1) {
			if (c == 'X') {
				placeValueUser[7][i] -= xDelim[i];
				placeValueCPU[7][i] -= oDelim[i];
			}
			else {
				placeValueUser[7][i] -= oDelim[i];
				placeValueCPU[7][i] -= xDelim[i]; 
			}
		}
		else if (tur == 2) {
			if (c == 'X') {
				 placeValueCPU[7][i] -= xDelim[i];
				 placeValueUser[7][i] -= oDelim[i];
			}
			else {
				 placeValueCPU[7][i] -= oDelim[i];
				 placeValueUser[7][i] -= xDelim[i];
			}
		}
	}

}
//prints the board
void Board::printBoard() {

	for (int i = 0; i < board.size(); i++) {
		cout << 8 - i << " | ";
		for (int j = 0; j < board.at(i).size(); j++) {
			cout << board.at(i).at(j) << " | ";
		}
		cout << "\n";
	}
	cout << "    1   2   3   4   5   6   7   8 " << endl;
}

//builds the board
void Board::buildBoard() {
	for (int i = 0; i<8; i++) {
		board.push_back(initialize());
		placeValueUser.push_back(valuePlace());
		placeValueCPU.push_back(valuePlace());
	}
	
}
Board::Board()
{
	

}