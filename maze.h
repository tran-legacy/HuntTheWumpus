/****************************
 * Tran Le
 * CSS342: Project #6 Hunt the Wumpus
 * 15 hours 
 * Vim on Cygwin
*****************************/

/////////////////////////////////////////////
//maze.h makes a maze class that represents a maze that
// - holds 4 pits, 4 bats, and 1 wumpus monster
// - implements the functionality of the Hunt the Wumpus game 
// - Implements the player functions 
/////////////////////////////////////////////

#ifndef MAZE_H
#define MAZE_H
#include "room.h"
#include <string>
using namespace std;

class Maze {
public: 
	// Constructor and Destructor
	Maze(); 
	virtual ~Maze() {} 
	
	void safeStart(); 
	void moveBatRandom(const int y, const int x);
	void printMaze() const;
	void checkAdjacent() const; 

	int getRoomNumber() const;

	// Player move functions
	bool moveUpSuccessfully(); 
	bool moveDownSuccessfully(); 
	bool moveLeftSuccessfully(); 
	bool moveRightSuccessfully();
	bool movePlayerSuccessfully(const int y, const int x);
   	// Player shoot functions	
	bool shootUpSuccessfully() const; 
	bool shootLeftSuccessfully() const; 
	bool shootDownSuccessfully() const; 
	bool shootRightSuccessfully() const;

	// Wumpus functions
	void moveWumpus();
	bool helpMoveWumpus(const int y, const int x);	
	bool wumpusAtePlayer();	

private: 
	static const int ROW = 8; 
	static const int COL = 8;	
	static const int MOD_VALUE = 8;
	// 2D array to represent the map that's made of rooms
	Room maze[COL][ROW];
	// Wumpus location
	int wumpusX, wumpusY;
	// Bats location 
	int bat1X, bat1Y; 
	int bat2X, bat2Y; 
	int bat3X, bat3Y; 
	int bat4X, bat4Y; 
	// Pits location
	int pit1X, pit1Y; 
	int pit2X, pit2Y; 
	int pit3X, pit3Y; 
	int pit4X, pit4Y;
	// Player location 
	int playerX, playerY; 
	
	bool isWall(const int y, const int x) const;
};
#endif // !MAZE_H
