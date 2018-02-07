#ifndef _ENEMY_H
#define _ENEMY_H
#include "Entity.h"
#include "Point.h"
#include "Wall.h"
#include <string>

class Player;

// Enemy
// Abstract class which represents an enemy entity with a move method
class Enemy: public Entity {
public:
    virtual ~Enemy();
    // Move the enemy according to it's AI. walls in an array of pointers to all walls in the level. player is a pointer to the player. width and height are the level's size. Should not move if not alive, returns true if enemy killed player, otherwise false
    virtual bool move(Wall **walls,int wallCount, Enemy **enemies,int enemyCount,Player *player, int width,int height) = 0;
    // Sets the state of the enemy to not alive.
    void die();
    // Returns true if enemy is alive, returns false otherwise
    bool isAlive();
    // Returns the type of enemy
    std::string getType();
protected:
    // The type of enemy, used in subclassing
    std::string type;
    // State of the enemy, alive or not alive
    bool alive;
    // Checks if currently on player, returns true if on player and kills it, otherwise false
    bool checkPlayer(Player *player);
};

#endif
