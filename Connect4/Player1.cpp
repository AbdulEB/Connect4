#include "stdafx.h"
#include "Board.h"
#include "iostream"
#include "Player1.h"
#include "gameplay.h"
#include <vector>
#include <string>
#include <thread>

using namespace std;
gameplay gp;
string name1;
bool winner = false;
int turns = 0;

void Player1::beginPlays() {	
	while (gp.getWinner() != true) {//while there is no winner
		if (gp.getTurn() == 1) {//if it is the players turn
			int columnPick = 0;
				while (columnPick < 1 || columnPick > 8) {
					cout << "Please enter a column between 1-8: " << endl;//player picks a column
					cin >> columnPick;
					if ((columnPick >= 1 && columnPick <= 8) && gp.countChecker().at(columnPick - 1) == 8) {
						cout << "Column is full pick another column number " << endl;
						columnPick = 0;
					}
				}
				columnPick--;
				//places a piece into that column
				gp.getBoard().placePiece(7 - gp.countChecker().at(columnPick), columnPick, gp.getUserPiece(), gp.getTurn());
				//checks if the user one
				winner = gp.getBoard().isWin(gp.getUserPiece());
				if (winner == true) {
					gp.setWinner();//set the game has one
					gp.getBoard().printBoard();//print board
					break;//breaks the loop
				}
				//count to increase the value of the bottom row
				if (gp.countChecker().at(columnPick) == 0) gp.incBottomRow();
				gp.incCountChecker(columnPick);//increases the count in a vector to be used to 
											//track the lowest available space per column

				gp.getBoard().printBoard();//print board
				if (gp.getBottomRow() == 8) {//checks to see if the board need to drop its lowest row
					gp.getBoard().drop(gp.getUserPiece(), gp.getTurn());//drops bottom row
					for (int i = 0; i < gp.countChecker().size(); i++) {
						gp.decCountChecker(i);//decrease the count per column by 1
					}
					//resets the bottom row value based on how many empty spaces is in the 
					//new bottom row
					for (int i = 0; i < gp.countChecker().size(); i++) {
						if (gp.countChecker().at(i) == 0) {
							gp.decBottomRow();
						}
					}
					gp.getBoard().printBoard();//print board after drop
				}

				cout << gp.countChecker().at(columnPick) << endl;
				gp.incOrder();//ends turn
		}
		
	}
}
//asks the user for the game
void Player1::beginGame() {
	
	cout << "Please enter Player'1 name: " << endl;
	cin >> name1;
	cout << "Player 1's name is  " << name1 << ". " << endl;
	gp.start();
}
//players names
string Player1::player1Name() {
	return name1;
}

Player1::Player1(gameplay* gameUser) {

	beginGame();//initializes the game
	gammy = gameUser;//gaming resource


}
