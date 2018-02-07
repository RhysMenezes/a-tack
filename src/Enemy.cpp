#include "Enemy.h"
#include "Player.h"
#include <string>

using namespace std;

Enemy::~Enemy() {
    // Default deconstructor
}

void Enemy::die() {
    alive = false;
    return;
}

bool Enemy::isAlive() {
    return alive;
}

string Enemy::getType() {
    return type;
}

bool Enemy::checkPlayer(Player *player) {
    if (((position.y) == (player->getPosition().y)) && ((position.x) == (player->getPosition().x))) {
        player->die();
        return true;
    }
    return false;
}
