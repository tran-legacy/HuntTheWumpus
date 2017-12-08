/****************************
 * Tran Le
 * CSS342: Project #6 Hunt the Wumpus
 * 15 hours
 * Vim on Cygwin
*****************************/

////////////////////////////////////
// room.cpp is the implementation of room.h
////////////////////////////////////

#include "room.h" 

/*************CONSTRUCTOR*****************/
Room::Room() {
    // Start out with empty room
    for (int row = 0; row < ROW; ++row) {
        for (int col = 0; col < COL; ++col) {
            room[row][col] = ' ';
        }
    }
	this->wumpus = false;
    this->bat = false;
    this->pit = false;
    this->footPrint = false;
}

/***************GET FUNCTIONS*********************/ 
char Room::getTopLeft() const {
	return room[0][0]; 
}
char Room::getTopRight() const {
	return room[0][1];
}
char Room::getBottomLeft() const {
	return room[1][0]; 
}
char Room::getBottomRight() const {
	return room[1][1]; 
}
int Room::getRoomNumber() const {
	return this->roomNumber;
}
/*************SET FUNCTIONS*********************/ 
void Room::setWumpus() {
	room[0][0] = WUMPUS;
	this->wumpus = true; 
}
void Room::setPit() {
	room[0][1] = PIT;
    this->pit = true;
}
void Room::setBat() {
	room[1][0] = BAT; 
	this->bat = true;
}
void Room::setPlayer() {
	room[1][1] = PLAYER;
	this->player = true;
	this->footPrint = true;
}
void Room::setRoomNumber(const int num) {
	this->roomNumber = num;
}

/**************REMOVE FUNCTIONS*****************/ 
void Room::removeBat() {
	room[1][0] = EMPTY;
	this->bat = false; 
}

void Room::removePlayer() {
	room[1][1] = EMPTY; 
	this->player = false;
}

void Room::removeWumpus() {
	room[0][0] = EMPTY;
	this->wumpus = false;
}

/****************BOOL FUNCTIONS*****************/ 
bool Room::hasFootPrint() const {
	return this->footPrint; 
}
bool Room::hasWumpus() const {
	return this->wumpus; 
}
bool Room::hasBat() const {
	return this->bat;
}
bool Room::hasPit() const {
	return this->pit;
}
