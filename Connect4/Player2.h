#pragma once
#include "gameplay.h"
class Player2
{
public: //header file of the computer player class that other allows other classes to
	//	access its resources
	gameplay* gammy; //resource that will be passed to the computer player class
	void startThread();
	Player2(gameplay* gameAI);
};

