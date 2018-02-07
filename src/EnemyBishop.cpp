#include "Enemy.h"
#include "Point.h"
#include "Entity.h"
#include "Wall.h"
#include "Player.h"
#include "stdlib.h"
#include "math.h"
#include "EnemyBishop.h"
#include "PrintUtils.h"
#include <iostream>
#include <string>
#include <stdlib.h> 

using namespace std;

EnemyBishop::EnemyBishop() {
    alive = true;
    type = "bishop";
}

EnemyBishop::~EnemyBishop() {
    
}

int EnemyBishop::updateDistance(Player *player) {
	// Set current distances using pythagora's theorem
	dist = sqrt(pow((position.x - (player->getPosition().x)),2) + pow((position.y - (player->getPosition().y)),2));
	
    // Store move distances
    // 0 = Left Up
    // 1 = Right Up
    // 2 = Left Down
    // 3 = Right Down
	storeDistance[0] = sqrt(pow(((position.x - 1) - (player->getPosition().x)),2) + pow(((position.y-1) - (player->getPosition().y)),2));
    storeDistance[1] = sqrt(pow(((position.x + 1) - (player->getPosition().x)),2) + pow(((position.y-1) - (player->getPosition().y)),2));
    storeDistance[2] = sqrt(pow(((position.x-1) - (player->getPosition().x)),2) + pow(((position.y + 1) - (player->getPosition().y)),2));
    storeDistance[3] = sqrt(pow(((position.x+1) - (player->getPosition().x)),2) + pow(((position.y + 1) - (player->getPosition().y)),2));

    // Get optimum move and return index of it to try first
	int index = 0;
	for (int i=0;i<4;i++){
        if (storeDistance[i] < storeDistance[index]) {
			index = i;
        }
	}
	return index;
}

bool EnemyBishop::move(Wall **walls,int wallCount, Enemy **enemies,int enemyCount,Player *player, int width,int height) {

	// Update distances
	int smallest = updateDistance(player);

	// Try smallest distance move
	if ((smallest==0) && (check(walls, wallCount, enemies, enemyCount, player, width, height, -1, -1, "up"))) {
		setPosition(position.x - 1, position.y - 1);

        // Check for player
        return checkPlayer(player);
	} else if ((smallest == 1) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 1, -1, "up"))) {
		setPosition(position.x + 1, position.y-1);

        // Check for player
        return checkPlayer(player);
	} else if ((smallest == 2) && (check(walls, wallCount, enemies, enemyCount, player, width, height, -1, 1, "down"))) {
		setPosition(position.x-1, position.y + 1);

        // Check for player
        return checkPlayer(player);
	} else if ((smallest == 3) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 1, 1, "down"))) {
		setPosition(position.x+1, position.y + 1);

        // Check for player
        return checkPlayer(player);
	}

    // Attempt other moves, only moving if it brings the enemy closer to the player
	if ((storeDistance[0]<dist) && (check(walls,wallCount,enemies,enemyCount,player,width,height,-1, -1, "up"))){
		setPosition(position.x-1, position.y-1);
        
        // Check for player
        return checkPlayer(player);
	} else if ((storeDistance[1]<dist) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 1, -1, "up"))) {
		setPosition(position.x + 1, position.y-1);

        // Check for player
        return checkPlayer(player);
	} else if ((storeDistance[2]<dist) && (check(walls, wallCount, enemies, enemyCount, player, width, height, -1, 1, "down"))) {
		setPosition(position.x-1, position.y+1);

        // Check for player
        return checkPlayer(player);
	} else if ((storeDistance[3]<dist) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 1, 1, "down"))) {
		setPosition(position.x+1, position.y+1);

        // Check for player
        return checkPlayer(player);
	}
    return false;
}

bool EnemyBishop::check(Wall **walls, int wallCount, Enemy **enemies, int enemyCount, Player *player, int width, int height, int moveX, int moveY, string direction) {

	if (direction == "up") {
        // Check walls
		for (int j = 0; j < wallCount; j++) {
			if (((position.y +moveY) == walls[j]->getPosition().y) && ((position.x+moveX) == walls[j]->getPosition().x)) {
				return false;
			}
		}
		// Check enemies
		for (int k = 0; k < enemyCount; k++) {
			if (enemies[k]->isAlive()&&((position.y +moveY) == enemies[k]->getPosition().y) && ((position.x+moveX) == enemies[k]->getPosition().x)) {
				return false;
			}
		}
		// Check bounds
		if (((position.y + moveY) < 0) || (position.x+moveX>= width))  {
			return false;
		}
		// Check bounds
		if (((position.y + moveY) >= height) || ((position.x +moveX) < 0)) {
			return false;
		}
	} else if (direction == "down") {
        // Check walls
		for (int j = 0; j < wallCount; j++) {
			if ((position.x +moveX) == (walls[j]->getPosition().x) && ((position.y+moveY) == (walls[j]->getPosition().y))) {
				return false;
			}
		}
		//check enemies
		for (int k = 0; k<enemyCount; k++) {
			if (enemies[k]->isAlive()&&((position.x + moveX) == (enemies[k]->getPosition().x)) && ((position.y+moveY) == (enemies[k]->getPosition().y))) {
				return false;
			}
		}
        // Check bounds
        if (((position.y + moveY) < 0) || (position.x+moveX>= width))  {
            return false;
        }
        // Check bounds
        if (((position.y + moveY) >= height) || ((position.x +moveX) < 0)) {
            return false;
        }
	}
	return true;
}

string EnemyBishop::draw() {
    return escapeCodeBase("32")+"x"+colourReset();
}
