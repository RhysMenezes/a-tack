#ifndef _ENEMY_STANDARD_H
#define _ENEMY_STANDARD_H
#include "Enemy.h"
#include "Entity.h"
#include "Point.h"
#include "Wall.h"
#include <string>

class Player;

// Enemy
// Represents a bishop
class EnemyStandard: public Enemy {
public:
    EnemyStandard();
    ~EnemyStandard();
    // Move the enemy according to it's AI. walls in an array of pointers to all walls in the level. player is a pointer to the player. width and height are the level's size. Should not move if not alive, returns true if enemy killed player, otherwise false
    bool move(Wall **walls,int wallCount, Enemy **enemies,int enemyCount,Player *player, int width,int height);
    // Returns the drawn enemy, includes formatting
    static std::string draw();
private:
    // Updates the distance properties based on the player
    int updateDistance(Player *player);
    // Distances away from the player at each possible movement position
    double storeDistance[4];
    // Current distance away from the player
    double dist;

    // Check if move is possible
    bool check(Wall **walls, int wallCount, Enemy **enemies, int enemyCount, Player *player, int width, int height, int move, std::string direction);
};

#endif
