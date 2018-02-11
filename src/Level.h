#ifndef _LEVEL_H
#define _LEVEL_H
#include "Player.h"
#include "Enemy.h"
#include "Entity.h"
#include "Point.h"
#include <string>

// Level
// Stores level structure and holds player and enemies
class Level {
public:
    Level();
    ~Level();
    // Creates level, takes string defining level size and structure, returns false if there was an issue loading the level
    bool load(std::string levelData,int width,int height);
    // Returns true if game is being played, false if game should be stopped
    bool isPlaying();
    // Reloads the level, returning it to it's original configuration
    void reload();
    // Outputs the game grid
    bool draw();
    // Take user input and move the player accordingly, returns true if move was successful, false if level should be quit
    int playerMove();
    // Allow all enemies to move, returns false if player was killed and game should be restarted
    bool enemiesMove();
    // Returns the number of turns the player has made
    int getTurns();
private:
    // Level data
    std::string levelData;
    // Size of the level
    int width;
    int height;
    // Player of the level
    Player *player;
    // Array of walls placed in the level
    Wall **walls;
    // Count of how many walls are in the walls array
    int wallCount;
    // Array of enemies in the level
    Enemy **enemies;
    // Count of how many enemies are in the enemies array
    int enemyCount;
    // Determines if the level should continue playing or should end
    bool playing;
    // How many turns the player made
    int turns;
};

#endif
