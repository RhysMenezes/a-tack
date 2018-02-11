#include "App.h"
#include "Game.h"
#include "Level.h"
#include "PrintUtils.h"
#include "Player.h"
#include "EnemyStandard.h"
#include "EnemyBishop.h"
#include "EnemyRook.h"
#include "Wall.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

App::App() {
    running = true;
}

App::~App() {

}

void App::run() {
    // Main runtime loop
    showTitle();

    // Continue to ask for a level and then play that level, allowing for user to quit and access help
    while (running) {
        Level *level = selectLevel();
        if (level == NULL) {
            delete level;
            continue;
        }

        //get single character inputs only
        getSingleChar();

        Game *game = new Game(level);
        clearScreen();

        // Reload the level is user instructs it
        while (game->play()) {
            delete game;
			level->reload();
            game = new Game(level);
            clearScreen();
        }

        clearScreen();
        delete level;
        delete game;
    }

    quit();
}

void App::showTitle() {
    // Print ASCI art of title with colouring
    clearScreen();

    string atC = "96";
    string tackC = "91";

    cout << colourBold() << escapeCodeBase(tackC) + "         _             _" << endl;
    cout << escapeCodeBase(atC) + "   ____"+escapeCodeBase(tackC)+" | |           | |" << endl;
    cout << escapeCodeBase(atC)+"  / __ \\"+escapeCodeBase(tackC)+"| |_ __ _  ___| | __" << endl;
    cout << escapeCodeBase(atC)+" / / _` "+escapeCodeBase(tackC)+"| __/ _` |/ __| |/ /" << endl;
    cout << escapeCodeBase(atC)+"| | (_| "+escapeCodeBase(tackC)+"| || (_| | (__|   <" << endl;
    cout << escapeCodeBase(atC)+" \\ \\__,_"+escapeCodeBase(tackC)+"|\\__\\__,_|\\___|_|\\_\\ " << endl;
    cout << escapeCodeBase(atC)+"  \\____/" << endl << endl;

    cout << escapeCodeBase("37") << "Developed by Dallas McNeil and Rhys Menezes"+ colourReset() << endl << endl;
}

void App::showHelp() {
    // Show help and instructions on how to play
    cout << endl;
    cout << colourBold() << "Level select commands" << colourReset() << endl;
    cout << "'q': Quit the game." << endl;
    cout << "'<levelname>': Attempts to load and play a level called <levelname>." << endl;
    cout << colourBold() << "Example levels: " << colourReset() << "easy1, easy2, easy3, easy4, easy5\n                med1, med2, med3, med4\n                hard1, hard2" << endl << endl;

    cout << colourBold() << "Game commands" << colourReset() << endl;
    cout << "'w': Move player up." << endl;
    cout << "'a': Move player left." << endl;
    cout << "'s': Move player down." << endl;
    cout << "'d': Move player right." << endl;
    cout << "'e': Wait one turn." << endl;
    cout << "'q': Quit the game." << endl << endl;

    cout << colourBold() << "Gameplay" << colourReset() << endl;
    cout << "The game consists of a grid. Each cell can be inhabited by the player, a wall, or an enemy. The grid is displayed, showing where everything is. The player then has the opertunity to move or stay still. Once the player makes their move, all enemies will move as well. The goal is for the player to kill all the enemies by moving onto them in their turn. However, if an enemy moves onto the player during their turn, it's game over." << endl << endl;

    cout << Player::draw() << ": The player" << endl;
    cout << Wall::draw() << ": A Wall. A cell where players and enemies cannot move onto." << endl;
    cout << EnemyStandard::draw() << ": Standard Enemy. Moves one cell up, down, left or right towards the player." << endl;
    cout << EnemyRook::draw() << ": Leaper Enemy. Can also move two cell up, down, left or right towards the player, but only moves when the player is in the same row or column." << endl;
    cout << EnemyBishop::draw() << ": Odd Enemy. Only moves diagonally one cell towards the player." << endl << endl;
}

Level *App::selectLevel() {
    // Get user input on what level to play
    string command;
    cout << "Which level do you want to play? Type 'h' for help or 'q' to quit.\n > ";
    cin >> command;

    // If command is quit or help, do the corresponding action, otherwise attempt to load the corresponding level file, display error if it doesn't exist
    if ("quit" == command || "q" == command) {
        running = false;
        return NULL;
    } else if ("help" == command || "h" == command) {
        showHelp();
        return NULL;
    } else {
        string line;
        string fileData;
        ifstream file("levels/"+command+".txt");
        int width = 0;
        int height = 0;

        // Read in level data into flat string
        if (file.is_open()) {
            int currentLine = 0;
            while (getline(file,line)) {
                if (currentLine == 0) {
                    width = stoi(line);
                } else if (currentLine == 1) {
                    height = stoi(line);
                } else {
                    fileData+=line;
                    fileData+=";";
                }
                currentLine++;
            }
            file.close();
        } else {
            cout << escapeCodeBase("91")+"ERROR:"+escapeCodeBase("31")+" Level doesn't exist."+colourReset() << endl;
            return NULL;
        }

        // Create a level from the level data, display an error if it isn't correctly formatted
        Level* level = new Level();
        if (!level->load(fileData,width,height)) {
            cout << escapeCodeBase("91")+"ERROR:"+escapeCodeBase("31")+" Level couldn't be loaded."+colourReset() << endl;
            delete level;
            return NULL;
        }
        return level;
    }
}

void App::quit() {
    cout << endl << colourBold()+"Thanks for playing!"+colourReset() << endl << endl;
    return;
}
