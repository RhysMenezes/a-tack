#ifndef _GAME_H
#define _GAME_H
#include "Level.h"

// Level
// Stores level structure and holds player and enemies
class Game {
public:
    // Initialises a game with a level
    Game(Level *level);
    ~Game();
    // Plays the level, returns true if should play level from start again, returns false if new level should be selected
    bool play();
private:
    // Stores the current level of the game
    Level *level;
};

#endif
