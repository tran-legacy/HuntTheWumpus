/****************************
 * Tran Le
 * CSS342: Project #6 Hunt the Wumpus
 * 15 hours 
 * Vim on Cygwin
*****************************/

//////////////////////////////////////
// room.h is implementation of a single Room that
// lays in a maze. 
// - The room is represented by a 2 by 2 array that could hold
// a pit, a wumpus, a bat, and/or a player
// - There are set, get, remove, and get bool functions 
//////////////////////////////////////

#ifndef ROOM_H
#define ROOM_H

class Room {
public:
	// Constructor and Destructor
	Room(); 
	virtual ~Room() {} 
	
	// Get functions
	char getTopLeft() const; 
	char getTopRight() const; 
	char getBottomLeft() const; 
	char getBottomRight() const; 
	int getRoomNumber() const; 

	// Set functions
    void setWumpus();
    void setPit();
    void setBat();
    void setPlayer();
	void setRoomNumber(const int num);

	// Remove functions
	void removeBat(); 
	void removePlayer();
    void removeWumpus(); 	

	// Bool variable functions
	bool hasFootPrint() const; 
	bool hasWumpus() const; 
	bool hasBat() const; 
	bool hasPit() const;

private: 
	static const int ROW = 2, COL = 2; 
	char room[ROW][COL];  
	bool wumpus, bat, pit, footPrint, player; 	
	int roomNumber;
	// Consts variables
	static const char EMPTY = ' '; 
	static const char PIT = 'O'; 
	static const char WUMPUS = '@'; 
	static const char BAT = '^'; 
	static const char PLAYER = '$'; 
};
#endif // !ROOM_H
