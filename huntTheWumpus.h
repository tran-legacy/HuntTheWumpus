/****************************
 * Tran Le
 * CSS342: Project #6 Hunt the Wumpus
 * 15 hours
 * Vim on Cygwin
*****************************/

////////////////////////////////////////
// HuntTheWumpus class pulls together what the Maze class has
// to create the game
// - it contains rules and controls of the game 
// - it keeps track of player's shots (arrows) 
// - takes in user input and process them 
////////////////////////////////////////

#ifndef HUNT_THE_WUMPUS
#define HUNT_THE_WUMPUS
#include <string> 
#include "maze.h"

using namespace std; 

class HuntTheWumpus {
public:
	// Constructor and Destructor
	HuntTheWumpus(); 
	virtual ~HuntTheWumpus(){}

	// Functions
	void startGame();

private: 
	Maze player;
    int arrows = 4;	
	
	// Private helper functions
	void clear(); // Clears the cmd screen so only the game is showing
	void shotMissed(); 
};
#endif // !HUNT_THE_WUMPUS
