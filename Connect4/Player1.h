#pragma once
#include "gameplay.h"
class Player1
{ //header file of the user player class that other allows other classes to access
	//	its resources
private:
		gameplay* gammy; //resource that will be passed to the computer player class
public:

	void beginPlays();
	void beginGame();
	std::string player1Name();
	Player1(gameplay* gameUser);
};

