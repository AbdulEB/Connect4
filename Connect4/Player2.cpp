#include "stdafx.h"
#include "Board.h"
#include "iostream"
#include "Player2.h"
#include <vector>
#include <string>
#include "gameplay.h"
#include <thread>
#include "Player1.h"

using namespace std;
bool winner2 = false; //to check if AI has won later

int selectColumn(gameplay* g_p) {
	//int s = rand() % 8;
	int user=0, AI=0, choose, s;
	vector<int> userHighest, cpuHighest, combined;
	//checks for the highest place value for the user and AI
	for (int i = 0; i < 8; i++) {
		if ((7 - g_p->countChecker().at(i)) >= 0) {
			if (user <= g_p->getBoard().getUserValue(7 - g_p->countChecker().at(i), i)) {
				user = g_p->getBoard().getUserValue(7 - g_p->countChecker().at(i), i);
			}
			if (AI <= g_p->getBoard().getCPUValue(7 - g_p->countChecker().at(i), i)) {
				AI = g_p->getBoard().getCPUValue(7 - g_p->countChecker().at(i), i);
			}
		}
		
	}
	//checks if there are any other that is equal to the above and places it into and array
	for (int i = 0; i < 8; i++) {
		if ((7 - g_p->countChecker().at(i)) >= 0) {
			if (user == g_p->getBoard().getUserValue(7 - g_p->countChecker().at(i), i)) {
				userHighest.push_back(i);

			}
			if (AI == g_p->getBoard().getCPUValue(7 - g_p->countChecker().at(i), i)) {
				cpuHighest.push_back(i);
			}
		}
	}
	//if user value is higher then AI, then AI will chooses a location that is benefit for the user
	if (user+1 > AI) {
		choose = rand() % userHighest.size();
		return s = userHighest.at(choose);
	}
	//if AI value is higher then user, then AI will chooses a location that is benefit for self
	else if (user < AI) {
		choose = rand() % cpuHighest.size();
		return s = cpuHighest.at(choose);
	}
	else {
	//	return s = rand() % 8;
		//chooses the highest valuable place between players
		for (int i = 0; i < userHighest.size(); i++) {
			for (int j = 0; j < cpuHighest.size(); j++) {
				if (userHighest.at(i) == cpuHighest.at(j)) {
					combined.push_back(userHighest.at(i));
				}
			}
		}
		if (combined.size() == 0) {
			for (int i = 0; i < userHighest.size(); i++) {
				combined.push_back(userHighest.at(i));
			}
			for (int i = 0; i < cpuHighest.size(); i++) {
				combined.push_back(cpuHighest.at(i));
			}
		}
		choose = rand() % combined.size();
		return s = combined.at(choose);
	}

	
}
void doAI(gameplay* g_p) { //mirror method the user player beginPlays() method
	while (!g_p->getWinner()) {
		if (g_p->getTurn() == 2) {
			int  columnPick;
			columnPick = selectColumn(g_p);
			while (g_p->countChecker().at(columnPick) == 8) {
				columnPick = selectColumn(g_p);
			}
			g_p->getBoard().placePiece(7 - g_p->countChecker().at(columnPick), columnPick, g_p->getCPUPiece(), g_p->getTurn());
			winner2 = g_p->getBoard().isWin(g_p->getCPUPiece());
			if (winner2 == true) {
				g_p->getBoard().printBoard();
				g_p->setWinner();
				break;
			}

			if (g_p->countChecker().at(columnPick) == 0) g_p->incBottomRow();
			g_p->incCountChecker(columnPick);
			g_p->getBoard().printBoard();
			if (g_p->getBottomRow() == 8) {
				g_p->getBoard().drop(g_p->getCPUPiece(), g_p->getTurn());
				for (int i = 0; i < g_p->countChecker().size(); i++) {
					g_p->decCountChecker(i);
				}
				for (int i = 0; i < g_p->countChecker().size(); i++) {
					if (g_p->countChecker().at(i) != 0) {
						g_p->decBottomRow();
					}
				}
				g_p->getBoard().printBoard();
			}
			cout << g_p->countChecker().at(columnPick) << endl;
			g_p->decOrder();
		}
		

	}
}

void Player2::startThread() { //Thread method
	thread MyThread(doAI, gammy); //paths resource to thread
	MyThread.detach();//detach thread
}
Player2::Player2(gameplay* gameAI) {//path the resource to constructor
	gammy = gameAI;
	
	string name2 = "Connie";
	cout << "CPU's name is  " << name2 << ". " << endl;



}