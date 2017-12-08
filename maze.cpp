/****************************
 * Tran Le
 * CSS342: Project #6 Hunt the Wumpus
 * 15 hours
 * Vim on Cygwin
*****************************/

////////////////////////////////////
// maze.cpp is the implementation of maze.h
////////////////////////////////////
#include "maze.h" 
#include <cstdlib>
#include <ctime>
#include <iostream> 

using namespace std;

static const string IS_WALL = "You can't move this way. There's a wall.";
static const string FOOTPRINT = "You see your footprints on the ground."; 
/**************CONSTRUCTOR************/
// Randomly put 4 pits, 4 bats, and 1 Wumpus in the maze
Maze::Maze() {
	// Give each room a room number
	int roomNum = 1; 
	for (int r = 0; r < ROW; ++r) {
		for (int c = 0; c < COL; ++c) {
			// set number in maze then increment it
			maze[r][c].setRoomNumber(roomNum++); 
		}
	}
	srand(time(0)); 
	// Random coordinates for 4 bats
	this->bat1X = rand()%MOD_VALUE;
	this->bat1Y = rand()%MOD_VALUE;
	this->bat2X = rand()%MOD_VALUE;
	this->bat2Y = rand()%MOD_VALUE;
	this->bat3X = rand()%MOD_VALUE;
	this->bat3Y = rand()%MOD_VALUE;
	this->bat4X = rand()%MOD_VALUE;
	this->bat4Y = rand()%MOD_VALUE;
	// Random coordinates for 4 pits
	this->pit1X = rand()%MOD_VALUE;
    this->pit1Y = rand()%MOD_VALUE;
    this->pit2X = rand()%MOD_VALUE;
    this->pit2Y = rand()%MOD_VALUE;
    this->pit3X = rand()%MOD_VALUE;
    this->pit3Y = rand()%MOD_VALUE;
    this->pit4X = rand()%MOD_VALUE;
    this->pit4Y = rand()%MOD_VALUE;
	// Random coordinate for Wumpus
	this->wumpusX = rand()%MOD_VALUE; 
	this->wumpusY = rand()%MOD_VALUE;  

	// Set the 4 bats in the respective coordinates
	maze[bat1Y][bat1X].setBat();
	maze[bat2Y][bat2X].setBat();
	maze[bat3Y][bat3X].setBat();
	maze[bat4Y][bat4X].setBat();
	// Set the 4 pits in the respective coordinates
	maze[pit1Y][pit1X].setPit();
	maze[pit2Y][pit2X].setPit();
	maze[pit3Y][pit3X].setPit();
	maze[pit4Y][pit4X].setPit();
	// Set coordinate for wumpus 
	maze[wumpusY][wumpusX].setWumpus();
	// Set player in a safe spot
	safeStart(); 	
}

/********************FUNCTIONS*******************/ 
//// Function to set player in safe spot in the maze ////
void Maze::safeStart() {
	bool safe = false; 
	do {
		this->playerX = rand()%MOD_VALUE;
		this->playerY = rand()%MOD_VALUE;
		// if player is starting in room with a wumpus, pit, or bat, then 
		// get new coordinate
		if (maze[playerY][playerX].hasPit() || maze[playerY][playerX].hasWumpus() || 
		    maze[playerY][playerX].hasBat() ) {
			this->playerX = rand()%MOD_VALUE; 
			this->playerY = rand()%MOD_VALUE; 
		} else { // else the room is safe and set the player in that room 
			maze[playerY][playerX].setPlayer();
		   	checkAdjacent();	
			safe = true;
		}

	} while (!safe);

}

//// Moves the bat in the given room to another random room ////
//// the past in y and x are the coordinate of the given room ////
//// Checks for the case where there's already a bat in the given room //// 
void Maze::moveBatRandom(const int y, const int x) {
	// Remove bat from the given room
	maze[y][x].removeBat();
	// Find new y and x coordinate to set the new bat in 
	bool okay = false; 
	do {
		int newY = rand()%MOD_VALUE; 
		int newX = rand()%MOD_VALUE;
		// If the coordinate does not have a bat in, set the bat
		if (!maze[newY][newX].hasBat()) { 
			maze[newY][newX].setBat(); 
			okay = true; 
		} 
	} while (!okay);

}


/************************WUMPUS FUNCTIONS*******************************/
//// Moves the Wumpus randomly to an adjacent room ////
//// If it's a wall, the Wumpus will stay in place //// 
//// 0=up, 1=left, 2=down, 3=right, 4=stay ////
void Maze::moveWumpus() {
	bool okay = false; 
	while (!okay) {
		int randomNum = rand()%5; // Gives you a random # 0-4
		if (randomNum == 0 && helpMoveWumpus(wumpusY - 1, wumpusX)) { // If up and not a wall 
			maze[wumpusY--][wumpusX].removeWumpus(); // Remove the Wumpus from room it was in
			okay = true;
		} else if (randomNum == 1 && helpMoveWumpus(wumpusY, wumpusX - 1)) {
			maze[wumpusY][wumpusX--].removeWumpus();
			okay = true; 
		} else if (randomNum == 2 && helpMoveWumpus(wumpusY + 1, wumpusX)) {
			maze[wumpusY++][wumpusX].removeWumpus(); 
			okay = true;
		} else if (randomNum == 3 && helpMoveWumpus(wumpusY, wumpusX + 1)) {
			maze[wumpusY][wumpusX++].removeWumpus();
			okay = true; 
		} else if (randomNum == 4) { 
			okay = true; 
		}
	}
}

bool Maze::helpMoveWumpus(const int y, const int x ) {
	// If y and x is out of range, it's a wall 
	if (y == -1 || y == 8 || x == -1 || x == 8) {
		return false;
	} else { // it's not wall then  set the player in the position
		maze[y][x].setWumpus(); 
		return true;
	}

}

bool Maze::wumpusAtePlayer() {
	if (wumpusX == playerX && wumpusY == playerY) {
		cout << "The Wumpus entered the room and ate you!" << endl;
		cout << "GAME OVER" << endl;
		return true;
	} 
	return false;
}

/*****************************OTHER FUNCTIONS*******************************/
////Prints out maze with rooms and stuff in maze ////
void Maze::printMaze() const {
	for (int row = 0; row < ROW; ++row) {
		cout << "#########################" << endl;
		cout << "#";
		for (int col1 = 0; col1 < COL; ++col1) {
			cout << maze[row][col1].getTopLeft() << maze[row][col1].getTopRight() << "#";
		}
		cout << "\n#";
		for (int col2 = 0; col2 < COL; ++col2) {
			cout << maze[row][col2].getBottomLeft() << maze[row][col2].getBottomRight() << "#";
		}
		cout << endl;
	}
	cout << "#########################" << endl;
	cout << "@ = WUMPUS    O = PIT    ^ = BAT    $ = PLAYER" << endl;
}

//// Checks the rooms surrounding the player and cout warning strings ////
void Maze::checkAdjacent() const {
	if (playerY > 0 && maze[playerY - 1][playerX].hasBat() || 
		playerX > 0 && maze[playerY][playerX - 1].hasBat() ||
		playerY < 7 && maze[playerY + 1][playerX].hasBat() || 
		playerX < 7 && maze[playerY][playerX + 1].hasBat()) {
		cout << "WARNING: You hear bats in the distance." << endl; 
	} 
	if (playerY > 0 && maze[playerY - 1][playerX].hasPit() || 
		playerX > 0 && maze[playerY][playerX - 1].hasPit() ||
		playerY < 7 && maze[playerY + 1][playerX].hasPit() || 
		playerX < 7 && maze[playerY][playerX + 1].hasPit()) {
		cout << "WARNING: You feel a draft." << endl; 
	} 
	if (playerY > 0 && maze[playerY - 1][playerX].hasWumpus() || 
		playerX > 0 && maze[playerY][playerX - 1].hasWumpus() ||
		playerY < 7 && maze[playerY + 1][playerX].hasWumpus() || 
		playerX < 7 && maze[playerY][playerX + 1].hasWumpus()) {
		cout << "WARNING: You smell something rank." << endl; 
	}

}

//// Returns the room number that the player is in ////
int Maze::getRoomNumber() const {
	return maze[playerY][playerX].getRoomNumber(); 
}

/***************************PLAYER FUNCTIONS*****************************/
/* All the move functions are the same 
 * If the spot there's trying to move to is a wall 
 * A message will be printed.
 * Otherwise, the player is moved */

bool Maze::moveUpSuccessfully() { 
	if (isWall(playerY - 1, playerX)) return true;
	if (movePlayerSuccessfully(playerY - 1, playerX)) {
		return true;
	}
	return false; 
}

bool Maze::moveDownSuccessfully() {
	if (isWall(playerY + 1, playerX)) {
		return true;
	}
	if (movePlayerSuccessfully(playerY + 1, playerX)) { 
		return true;
	}	
	return false;
}

bool Maze::moveLeftSuccessfully() {
	if (isWall(playerY, playerX - 1)) return true; 
	if (movePlayerSuccessfully(playerY, playerX - 1)) {
		return true;
	}
	return false;
}

bool Maze::moveRightSuccessfully() {
	if (isWall(playerY, playerX + 1)) return true; 
	if (movePlayerSuccessfully(playerY, playerX + 1)) {
		return true;
	} 
	return false;
}

bool Maze::isWall(const int y, const int x) const {
	// If y and x is out of range, it's a wall 
	if (y == -1 || y == ROW || x == -1 || x == COL) {
		cout << IS_WALL << endl; 
		return true;
	} 
	return false;
}

//// Helper move player function to check for walls
//// check for pit, bat, wumpus and footprint ////
bool Maze::movePlayerSuccessfully(const int y, const int x) {
	if (maze[y][x].hasBat()) { // It's a bat-room
		maze[y][x].removeBat(); // remove bat the bat from the current room so it could move
		moveBatRandom(y, x); // move the bat to a random room
		cout << "A bunch of bats are flying you to another room!" << endl; 
		// Find new coordinates to put player in and remove player from current coordinate
		maze[playerY][playerX].removePlayer(); 
		playerY = rand()%MOD_VALUE;
		playerX = rand()%MOD_VALUE;
		movePlayerSuccessfully(playerY, playerX);
	}  else if (maze[y][x].hasPit()) { // It's a pit-room
		cout << "You've fallen into a pit and died!" << endl;
	   	cout << "GAME OVER" << endl; 	
		return false;
	} else if (maze[y][x].hasWumpus()) {
		cout << "You've woken up the Wumpus and it ate you!" << endl; 
		cout << "GAME OVER" << endl;
	   	return false; 	
	} else { // else it's a safe room and set the player in the position
		if (maze[y][x].hasFootPrint())
			cout << "You see footprints in the dust." << endl; 
		maze[playerY][playerX].removePlayer(); 
		playerY = y; 
		playerX = x; 
		maze[y][x].setPlayer();	
		return true;
	}
	

}

//// Returns whether or not the arrow hit the Wumpus  was successful ////
bool Maze::shootUpSuccessfully() const {
	// If the position up of player has a Wumpus
	return maze[playerY - 1][playerX].hasWumpus();	
}
bool Maze::shootLeftSuccessfully() const {
	return maze[playerY][playerX - 1].hasWumpus();
}
bool Maze::shootDownSuccessfully() const {
	return maze[playerY + 1][playerX].hasWumpus(); 
}
bool Maze::shootRightSuccessfully() const {
	return maze[playerY][playerX + 1].hasWumpus(); 
}

