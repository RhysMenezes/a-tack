#ifndef _WALL_H
#define _WALL_H
#include "Point.h"
#include <string>

// Wall
// Represents a wall in a level
class Wall:public Entity {
public:
    Wall();
    ~Wall();
    static std::string draw();
};

#endif
