#include "Player.h"
#include "Entity.h"
#include "Enemy.h"
#include "Point.h"
#include "PrintUtils.h"
#include "Wall.h"
#include <iostream>

using namespace std;

Player::Player(){
	status = true;
}

Player::~Player() {
	status = false;
}

bool Player::move(int direction, Enemy** enemies,int eCount, Wall **walls, int wCount, int width, int height) {
	// Attempt to move left
	if (direction == 0) {
        // Check bounds
        if ((position.x-1 < 0) || (position.x-1 >= width)) {
            return false;
        } else if ((position.y < 0) || (position.y >= height)){
            return false;
        }
        // Check for walls
		for (int i = 0; i < wCount; i++) {
			if ((walls[i]->getPosition().x == (position.x) - 1) && (walls[i]->getPosition().y == (position.y))) {
				return false;
			}
        }
        // Check for enemies
		for (int i = 0; i < eCount; i++) {
			if ((enemies[i]->getPosition().x == (position.x) - 1) && (enemies[i]->getPosition().y == (position.y))){
				if (enemies[i]->isAlive()) {
					enemies[i]->die();
				}
			}
		}
        
		setPosition(position.x - 1, position.y);
		return true;
	}
	// Attempt to move right
    if (direction == 1) {
        // Check bounds
        if ((position.x+1 < 0) || (position.x+1 >= width)) {
            return false;
        } else if ((position.y < 0) || (position.y >= height)){
            return false;
        }
        // Check for walls
		for (int i = 0; i < wCount; i++) {
			if ((walls[i]->getPosition().x == (position.x) + 1) && (walls[i]->getPosition().y == (position.y))) {
				return false;
			}
        }
        // Check for enemies
		for (int i = 0; i < eCount; i++) {
			if ((enemies[i]->getPosition().x == (position.x) + 1) && (enemies[i]->getPosition().y == (position.y))) {
				if (enemies[i]->isAlive()) {
					enemies[i]->die();
				}
			}
		}
        
		setPosition(position.x + 1, position.y);
		return true;
    }
    // Attempt to move up
    if (direction == 2) {
        // Check bounds
        if ((position.x < 0) || (position.x >= width)) {
            return false;
        } else if ((position.y-1 < 0) || (position.y-1 >= height)){
            return false;
        }
        // Check for walls
		for (int i = 0; i < wCount; i++) {
			if ((walls[i]->getPosition().y == (position.y) - 1) && (walls[i]->getPosition().x == (position.x))) {
				return false;
			}
        }
        // Check for enemies
		for (int i = 0; i < eCount; i++) {
			if ((enemies[i]->getPosition().y == (position.y) - 1) && (enemies[i]->getPosition().x == (position.x))) {
				if (enemies[i]->isAlive()) {
					enemies[i]->die();
				}
			}
		}
        
		setPosition(position.x, position.y - 1);
		return true;
	}
    // Attempt to move down
    if (direction == 3) {
        // Check bounds
        if ((position.x < 0) || (position.x >= width)) {
            return false;
        } else if ((position.y+1 < 0) || (position.y+1 >= height)){
            return false;
        }
        // Check for walls
		for (int i = 0; i < wCount; i++) {
			if ((walls[i]->getPosition().y == (position.y) + 1) && (walls[i]->getPosition().x == (position.x))) {
                return false;
			}
        }
        // Check for enemies
		for (int i = 0; i < eCount; i++) {
			if ((enemies[i]->getPosition().y == (position.y) + 1) && (enemies[i]->getPosition().x == (position.x))) {
				if (enemies[i]->isAlive()) {
					enemies[i]->die();
				}
			}
		}
        
		setPosition(position.x, position.y+1);
		return true;
	}
    return false;
}

bool Player::playerStatus() {
    return status;
}

void Player::die() {
    status = false;
}

string Player::draw() {
    return escapeCodeBase("96")+"@"+colourReset();
}
