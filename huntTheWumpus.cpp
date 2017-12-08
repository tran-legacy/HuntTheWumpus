/****************************
 * Tran Le
 * CSS342: Project #6 Hunt the Wumpus
 * 15 hours
 * Vim on Cygwin
*****************************/

////////////////////////////////////
// huntTheWumpus.cpp is the implementation of huntTheWumpus.h
////////////////////////////////////

#include "huntTheWumpus.h"
#include <iostream>
#include <iomanip>

static const string WUMPUS_KILLED = "You've killed the Wumpus. Congratulation! :)"; 
/****************CONSTRUCTOR****************/
HuntTheWumpus::HuntTheWumpus() {
	clear(); 
	cout << setw(50) << right << "*****HUNT THE WUMPUS*****" << endl; 
	cout << "Move through the maze, find the Wumpus, and kill him. ";
	cout << "But beware of the pits and the bats!\n" << endl; 
	cout << string(80, '*') << endl;
	cout << "RULES" << endl; 
	cout << "- You have four arrows to kill the Wumpus with. Use them wisely." << endl;
	cout << "- Each time you miss a shot, "; 
   	cout << "the Wumpus will randomly move to an adjacent room." << endl; 
	cout << "- Walking into a pit-room will be automatically kill you." << endl; 
	cout << "- When you walk into a bat-room, the bat will pick you up and "; 
	cout  << "fly you to a random room." << endl;
	cout << "- If you walk into a room with the Wumpus - he will eat you." << endl; 
	cout << string(80, '*') << endl;
    cout << "\n";	
	cout << "CONTROLS" << endl; 
	cout << "i" << string(10, '.') << setw(15) << left << "up" << "|" << setw(6) << " "
		 << "I" << string(10, '.') << "shoot up" << endl; 
	cout << "j" << string(10, '.') << setw(15) << left << "left" << "|" << setw(6) << " "
		 << "J" << string(10, '.') << "shoot left" << endl; 
	cout << "l" << string(10, '.') << setw(15) << left << "right" << "|" << setw(6) << " "
		 << "L" << string(10, '.') << "shoot right" << endl; 
	cout << "m" << string(10, '.') << setw(15) << left << "down" << "|" << setw(6) << " "
		 << "M" << string(10, '.') << "shoot down" << endl; 
	cout << "map" << string(8, '.') << "opens map" << setw(7) << right <<  "|" << endl;
	cout << endl;
}
//// Helper function to "clear" the cmd window screen so only the game would show
void HuntTheWumpus::clear() {
    // CSI[2J clears screen, CSI[H moves the cursor to top-left corner
    std::cout << "\x1B[2J\x1B[H";

}

//// How the game works ////
//// while the game is running, the method will take in user input////
//// and call the correct functions in the maze class called "player"////
void HuntTheWumpus::startGame() {
	string str;
	bool gameOver = false;	
	while (!gameOver) {
		if (arrows == 0) {
			cout << "You ran out of arrows! Game over :(" << endl;
			gameOver = true; 
			break;
		}
		player.checkAdjacent(); 
		cout << "Room Number: #" << player.getRoomNumber() << endl;
		cout << "Arrow(s) Left: " << this->arrows << endl;
		cout << "Enter in your action: "; 
		cin >> str;
		cout << "-------------------------------" << endl;

		// Player movement
	   	if (str.compare("i") == 0) {
			gameOver = !player.moveUpSuccessfully(); 
		} else if (str.compare("j") == 0) {
			gameOver = !player.moveLeftSuccessfully(); 
		} else if (str.compare("m") == 0) {
			gameOver = !player.moveDownSuccessfully(); 
		} else if (str.compare("l") == 0) {
			gameOver = !player.moveRightSuccessfully(); 
		}
		// Player shot
	   	else if (str.compare("I") == 0) {
			if (player.shootUpSuccessfully()) {
				cout << WUMPUS_KILLED << endl;
				gameOver = true;
			} else {
				shotMissed();
				if (player.wumpusAtePlayer()) 
					gameOver = true; 
			}
		} else if (str.compare("J") == 0) {
			if (player.shootLeftSuccessfully()) {
				cout << WUMPUS_KILLED << endl;
				gameOver = true;
			} else {
				shotMissed();
				if (player.wumpusAtePlayer())
				   	gameOver = true; 
			}
		} else if (str.compare("M") == 0) {
			if (player.shootDownSuccessfully()) {
				cout << WUMPUS_KILLED << endl;
				gameOver = true;
			} else {
				shotMissed();
				if (player.wumpusAtePlayer())
				   	gameOver = true; 
			} 
		} else if (str.compare("L") == 0) {
			if (player.shootLeftSuccessfully()) {
				cout << WUMPUS_KILLED << endl;
				gameOver = true;
			} else {
				shotMissed();
				if (player.wumpusAtePlayer())
					gameOver = true;
			}		
		// map printing
		} else if (str.compare("map") == 0) {
			player.printMaze(); 
		} else {
			cout << "Invalid input, try again" << endl;
		}
		cout << endl;
	}
	cout << "Thank you for playing!" << endl;
}



void HuntTheWumpus::shotMissed() {
	--arrows; 
   	cout << "You missed! You hear a rumbling in the distance." << endl;	
	player.moveWumpus(); 
}


