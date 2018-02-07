#ifndef _ENTITY_H
#define _ENTITY_H
#include "Point.h"
#include <string>

// Entity
// Represents an object in a level with a place on the grid
class Entity {
public:
    Entity();
    ~Entity();
    // Set the position of the entity
    void setPosition(int x,int y);
    // Get the position of the entity
    Point getPosition();
protected:
    // Stores the position of the entity
    Point position;
};

#endif
