#ifndef _PLAYER_H
#define _PLAYER_H

#include "Point.h"
#include "Entity.h"
#include "Enemy.h"
#include "Wall.h"

// Player
// Represents the player in the game
class Player:public Entity {
public:
    Player();
    ~Player();
    // Move the player according to the direction. walls in an array of pointers to all walls in the level. player is a pointer to the player. width and height are the level's size. Returns false if the move cannot be made
    bool move(int direction, Enemy** enemies, int eCount, Wall **walls, int wCount, int width, int height);
	// Get player status, alive or not alive
    bool playerStatus();
    // Returns the drawn enemy, includes formatting
    static std::string draw();
    // Sets the player status to not alive
    void die();
private:
	// True if alive, false if dead
	bool status;
};

#endif
