#include "Game.h"
#include "Level.h"
#include "PrintUtils.h"
#include <string>
#include <iostream>

using namespace std;

Game::Game(Level *level) {
    this->level = level;
}

Game::~Game() {
    
}

bool Game::play() {
    // Main game loop
    bool replay;
    while (level->isPlaying()) {
        // If all enemies are dead, returns true, show victory screen
        if (level->draw()) {
            cout << colourBold() << "You win!" << colourReset() << endl;
            cout << "You took " << colourBold() << level->getTurns() << colourReset() << " turns!" << endl << endl;
            replay = true;
            break;
        }
        // If player wants to quit, exit loop
        if (!level->playerMove()) {
            replay = false;
            break;
        }
        // If player died, exit loop and ask if they want to replay or quit
        if (!level->enemiesMove()) {
            replay = true;
            level->draw();
            cout << colourBold() << "You died!" << colourReset() << endl;
            break;
        }
    }
    if (replay) {
        // Get user input and quit if requested
        cout << "Type 'q' to quit or 'r' to retry." << endl;
        cout << " > ";
        string command;
        cin >> command;
        if ("q" == command||"quit" == command)  {
            replay = false;
        } else {
            replay = true;
        }
    }
    // If replay is true, level will be reloaded and a new game started, else level select will be shown
    return replay;
}
