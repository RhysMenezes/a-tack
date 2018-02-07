#include "Enemy.h"
#include "Point.h"
#include "Entity.h"
#include "Wall.h"
#include "Player.h"
#include "stdlib.h"
#include "math.h"
#include "PrintUtils.h"
#include "EnemyRook.h"
#include <iostream>
#include <string>
#include <stdlib.h> 

using namespace std;

EnemyRook::EnemyRook() {
    alive = true;
    type = "rook";
}

EnemyRook::~EnemyRook() {
    
}

int EnemyRook::updateDistance(Player *player) {
    // Set current distances using pythagora's theorem
    dist = sqrt(pow((position.x - (player->getPosition().x)),2) + pow((position.y - (player->getPosition().y)),2));

    // Store move distances
    // 0 = Left 1
    // 1 = Right 1
    // 2 = Up 1
    // 3 = Down 1
    // 4 = Left 2
    // 5 = Right 2
    // 6 = Up 2
    // 7 = Down 2
	storeDistance[0] = sqrt(pow(((position.x - 1) - (player->getPosition().x)),2) + pow((position.y - (player->getPosition().y)),2));
    storeDistance[1] = sqrt(pow(((position.x + 1) - (player->getPosition().x)),2) + pow((position.y - (player->getPosition().y)),2));
    storeDistance[2] = sqrt(pow(((position.x) - (player->getPosition().x)),2) + pow(((position.y - 1) - (player->getPosition().y)),2));
    storeDistance[3] = sqrt(pow(((position.x) - (player->getPosition().x)),2) + pow(((position.y + 1) - (player->getPosition().y)),2));
    storeDistance[4] = sqrt(pow(((position.x - 2) - (player->getPosition().x)),2) + pow((position.y - (player->getPosition().y)),2));
    storeDistance[5] = sqrt(pow(((position.x + 2) - (player->getPosition().x)),2) + pow((position.y - (player->getPosition().y)),2));
    storeDistance[6] = sqrt(pow(((position.x) - (player->getPosition().x)),2) + pow(((position.y - 2) - (player->getPosition().y)),2));
    storeDistance[7] = sqrt(pow(((position.x) - (player->getPosition().x)),2) + pow(((position.y + 2) - (player->getPosition().y)),2));

    // Get optimum move and return index of it to try first
    int index = 0;
	for (int i = 0; i < 8; i++) {
        if (storeDistance[i] < storeDistance[index]) {
			index = i;
        }
	}
    
    return index;
}

bool EnemyRook::move(Wall **walls,int wallCount, Enemy **enemies,int enemyCount,Player *player, int width,int height) {

    // Update distances
    int smallest = updateDistance(player);

    // Try smallest distance move
    if ((smallest==0) && (check(walls, wallCount, enemies, enemyCount, player, width, height, -1, "x"))) {
		setPosition(position.x - 1, position.y);

        // Check for player
        return checkPlayer(player);
	}
	else if ((smallest == 1) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 1, "x"))) {
		setPosition(position.x + 1, position.y);

        // Check for player
        return checkPlayer(player);
	} else if ((smallest == 2) && (check(walls, wallCount, enemies, enemyCount, player, width, height, -1, "y"))) {
		setPosition(position.x, position.y - 1);

        // Check for player
        return checkPlayer(player);
	} else if ((smallest == 3) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 1, "y"))) {
		setPosition(position.x, position.y + 1);

        // Check for player
        return checkPlayer(player);
    } else if ((smallest==4) && (check(walls, wallCount, enemies, enemyCount, player, width, height, -2, "x"))) {
        setPosition(position.x - 2, position.y);
        
        // Check for player
        return checkPlayer(player);
    } else if ((smallest == 5) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 2, "x"))) {
        setPosition(position.x + 2, position.y);
        
        // Check for player
        return checkPlayer(player);
    } else if ((smallest == 6) && (check(walls, wallCount, enemies, enemyCount, player, width, height, -2, "y"))) {
        setPosition(position.x, position.y - 2);
        
        // Check for player
        return checkPlayer(player);
    } else if ((smallest == 7) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 2, "y"))) {
        setPosition(position.x, position.y + 2);
        
        // Check for player
        return checkPlayer(player);
    } 

    // Attempt other moves, only moving if it brings the enemy closer to the player
	if ((storeDistance[0]<dist) && (check(walls,wallCount,enemies,enemyCount,player,width,height,-1, "x"))){
		setPosition(position.x-1, position.y);
        
        // Check for player
        return checkPlayer(player);
	} else if ((storeDistance[1]<dist) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 1, "x"))) {
		setPosition(position.x + 1, position.y);

        // Check for player
        return checkPlayer(player);
	} else if ((storeDistance[2]<dist) && (check(walls, wallCount, enemies, enemyCount, player, width, height, -1, "y"))) {
		setPosition(position.x, position.y-1);

        // Check for player
        return checkPlayer(player);
	} else if ((storeDistance[3]<dist) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 1, "y"))) {
		setPosition(position.x, position.y+1);

        // Check for player
        return checkPlayer(player);
    } else if ((storeDistance[4]<dist) && (check(walls,wallCount,enemies,enemyCount,player,width,height,-2, "x"))){
        setPosition(position.x-2, position.y);
        
        // Check for player
        return checkPlayer(player);
    } else if ((storeDistance[5]<dist) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 2, "x"))) {
        setPosition(position.x + 2, position.y);
        
        // Check for player
        return checkPlayer(player);
    } else if ((storeDistance[6]<dist) && (check(walls, wallCount, enemies, enemyCount, player, width, height, -2, "y"))) {
        setPosition(position.x, position.y-2);
        
        // Check for player
        return checkPlayer(player);
    } else if ((storeDistance[7]<dist) && (check(walls, wallCount, enemies, enemyCount, player, width, height, 2, "y"))) {
        setPosition(position.x, position.y+2);
        
        // Check for player
        return checkPlayer(player);
    }
    return false;
}

bool EnemyRook::check(Wall **walls, int wallCount, Enemy **enemies, int enemyCount, Player *player, int width, int height, int move, string direction) {
    // Check if player is in same column or row
    if (!(position.y == player->getPosition().y || position.x == player->getPosition().x)) {
        return false;
    }
    
    if (direction == "y") {
        // Check for walls
		for (int j = 0; j < wallCount; j++) {
			if (((position.y +move) == walls[j]->getPosition().y) && ((position.x) == walls[j]->getPosition().x)) {
				return false;
			}
		}
        // Check for enemies
		for (int k = 0; k < enemyCount; k++) {
			if (enemies[k]->isAlive()&&((position.y +move) == enemies[k]->getPosition().y) && ((position.x) == enemies[k]->getPosition().x)) {
				return false;
			}
		}
        // Check y bound
		if ((position.y + move) < 0) {
			return false;
        }
        // Check y bound
		if ((position.y + move) >= height) {
			return false;
		}
	}
    else if (direction == "x") {
        // Check for walls
		for (int j = 0; j < wallCount; j++) {
			if ((position.x +move) == (walls[j]->getPosition().x) && ((position.y) == (walls[j]->getPosition().y))) {
				return false;
			}
		}
		// Check for enemies
		for (int k = 0; k<enemyCount; k++) {
			if (enemies[k]->isAlive()&&((position.x + move) == (enemies[k]->getPosition().x)) && ((position.y) == (enemies[k]->getPosition().y))) {
				return false;
			}
		}
		// Check x bound
		if ((position.x + move) >= width) {
			return false;
		}
		// Check x bound
		if ((position.x +move) < 0) {
			return false;
		}
	}
	return true;
}

string EnemyRook::draw() {
    return escapeCodeBase("32")+"+"+colourReset();
}
