#include "Entity.h"
#include "Point.h"

Entity::Entity() {
    position.x = 0;
    position.y = 0;
}

Entity::~Entity() {
    
}

// Set the position of the entity
void Entity::setPosition(int x, int y) {
    this->position.x = x;
    this->position.y = y;
}

// Get the position of the entity
Point Entity::getPosition() {
    return position;
}
