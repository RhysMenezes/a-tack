#include "Level.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyStandard.h"
#include "EnemyRook.h"
#include "EnemyBishop.h"
#include "Entity.h"
#include "Wall.h"
#include "Point.h"
#include "PrintUtils.h"
#include <string>
#include <iostream>

using namespace std;

Level::Level() {
    playing = true;
    wallCount = 0;
    enemyCount = 0;
    turns = 0;
}

Level::~Level() {
    // Delete any walls from the array
    for (int i=0;i<wallCount;i++) {
        delete walls[i];
    }
    // Delete walls array if it existed
    if (wallCount > 0) {
        delete[] walls;
    }
    // Delete any enemies from the array
    for (int i=0;i<enemyCount;i++) {
        delete enemies[i];
    }
    // Delete enemies array if it existed
    if (enemyCount > 0) {
        delete[] enemies;
    }
    delete player;
}

bool Level::load(string levelData,int width, int height) {
    // Set level information
    this->width = width;
    this->height = height;
    this->levelData = levelData;

    // Create a player
    player = new Player();

    // Check if width and height are above 0
    if (width < 1||height < 1) {
        cout << escapeCodeBase("31")+"Invalid level size."+colourReset() << endl;
        return false;
    }

    int size = levelData.length();

    // Keep track of how many entities should be created
    int es = 0;
    int ws = 0;
    int ps = 0;

    // Record how many entities
    for (int i=0;i<size;i++) {
        if (levelData[i] == '*') {
            es++;
        } else if (levelData[i] == '#') {
            ws++;
        } else if (levelData[i] == '@') {
            ps++;
        } else if (levelData[i] == '+') {
            es++;
        } else if (levelData[i] == 'x') {
            es++;
        }
    }

    // Show an error if an incorrect number of players appeared
    if (ps != 1) {
        cout << escapeCodeBase("31")+"No or more than one player found."+colourReset() << endl;
        return false;
    }

    // If there are walls or entities, dynamically allocate arrays for them
    if (es > 0) {
        enemies = new Enemy*[es];
    }
    if (ws > 0) {
        walls = new Wall*[ws];
    }

    wallCount = ws;
    enemyCount = es;

    // Keep track of x and y coordinates of entities in data
    int x = 0;
    int y = 0;
    int w = 0;
    int e = 0;

    for (int i=0;i<size;i++) {
        // New row
        if (levelData[i] == ';') {
            y++;
            x = 0;
            continue;
        }
        // Set player position
        if (levelData[i] == '@') {
            player->setPosition(x,y);
        } else if (levelData[i] == '#') {
            // Create wall
            if (w > ws) {
                cout << escapeCodeBase("31")+"More walls found than expected."+colourReset() << endl;
                return false;
            }
            walls[w] = new Wall();
            walls[w]->setPosition(x,y);
            w++;
        } else if (levelData[i] == '*') {
            // Create standard enemy
            if (e > es) {
                cout << escapeCodeBase("31")+"More enemies found than expected."+colourReset() << endl;
                return false;
            }
            enemies[e] = new EnemyStandard();
            enemies[e]->setPosition(x,y);
            e++;
        } else if (levelData[i] == '+') {
            // Create rook enemy
            if (e > es) {
                cout << escapeCodeBase("31")+"More enemies found than expected."+colourReset() << endl;
                return false;
            }
            enemies[e] = new EnemyRook();
            enemies[e]->setPosition(x,y);
            e++;
        } else if (levelData[i] == 'x') {
            // Create bishop enemy
            if (e > es) {
                cout << escapeCodeBase("31")+"More enemies found than expected."+colourReset() << endl;
                return false;
            }
            enemies[e] = new EnemyBishop();
            enemies[e]->setPosition(x,y);
            e++;
        } 

        // Check x an y don't exceed specified width and height
        if (x>=width) {
            cout << escapeCodeBase("31")+"Width bound exceeded."+colourReset() << endl;
            return false;
        }
        if (y>=height) {
            cout << escapeCodeBase("31")+"Height bound exceeded."+colourReset() << endl;
            return false;
        }
        x++;
    }

    return true;
}

void Level::reload() {
    turns = 0;
    // Deconstruct objects and laod from level data again
    for (int i=0;i<wallCount;i++) {
        delete walls[i];
    }
    if (wallCount > 0) {
        delete[] walls;
    }
    for (int i=0;i<enemyCount;i++) {
        delete enemies[i];
    }
    if (enemyCount > 0) {
        delete[] enemies;
    }
    delete player;
    load(this->levelData,this->width,this->height);
}

bool Level::isPlaying() {
    return playing;
}

bool Level::draw() {
    clearScreen();

    // Create grid output as string with border of walls
    // Character representation of entities
    // A Wall
    // B Player
    // C Enemy Standard
    // D Enemy Rook
    // E Enemy Bishop
    string output(width+2, 'A');
    int add = 0;
    output+="\n";
    for (int y=0;y<height;y++) {
        for (int x=0;x<width+2;x++) {
            if (x==0) {
                output+="A";
            } else if (x==width+1) {
                output+="A";
            } else {
                output+=" ";
            }
        }
        output+="\n";
    }
    string end(width+2, 'A');
    output+=end;

    // Insert the player
    Point pos = player->getPosition();
    output.replace(((width+3)*(pos.y+1))+pos.x+1,1,"B");

    // Insert the walls
    for (int i=0;i<wallCount;i++) {
        pos = walls[i]->getPosition();
        output.replace(((width+3)*(pos.y+1))+pos.x+1,1,"A");
    }

    // Insert the enemies, based on their type, keeping track if they are all not alive
    bool allDead = true;
    for (int i=0;i<enemyCount;i++) {
        if (enemies[i]->isAlive()) {
            allDead = false;
            pos = enemies[i]->getPosition();
            if (enemies[i]->getType() == "standard") {
                output.replace(((width+3)*(pos.y+1))+pos.x+1,1,"C");
            } else if (enemies[i]->getType() == "rook") {
                output.replace(((width+3)*(pos.y+1))+pos.x+1,1,"D");
            } else if (enemies[i]->getType() == "bishop") {
                output.replace(((width+3)*(pos.y+1))+pos.x+1,1,"E");
            }
        }
    }

    // Replace numbers with coloured characters, based on each entities draw function
    size_t loc = output.find_first_of("ABCDE");
    while (loc!=string::npos) {
        switch (output[loc]) {
        case 'A':
            output.replace(loc,1,Wall::draw());
            break;
        case 'B':
            output.replace(loc,1,Player::draw());
            break;
        case 'C':
                output.replace(loc,1,EnemyStandard::draw());
            break;
        case 'D':
            output.replace(loc,1,EnemyRook::draw());
            break;
        case 'E':
            output.replace(loc,1,EnemyBishop::draw());
            break;
        }
        loc = output.find_first_of("ABCDE",loc+1);
    }

    // Output grid
    cout << output << endl << endl;
    // Return if all enemies are dead or not
    return allDead;
}

int Level::playerMove() {
    string command;
    int direction = -1;
    do {
        // Get player input and get command
        // 0 = Left
        // 1 = Right
        // 2 = Up
        // 3 = Down
        cout << " > ";
	      command = getSingleChar();

        if ("quit" == command||"q" == command) {
            return 2;
        } else if ("" == command||"e" == command||"wait" == command)  {
            turns++;
            return 1;
        } else if ("a" == command||"left" == command || "\033[D"==command)  {
            direction = 0;
        } else if ("d" == command||"right" == command || "\033[C"==command)  {
            direction = 1;
        } else if ("w" == command||"up" == command || "\033[A"==command)  {
            direction = 2;
        } else if ("s" == command||"down" == command || "\033[B"==command)  {
            direction = 3;
        } else if ("r" == command) {
            return 3;
        } else {
            // Output error and ask for input again
            cout << escapeCodeBase("91") << "Invalid command!" + colourReset() + " Try 'w' for down, 'a' for left, 's' for down, 'd' for right, 'e' to wait or 'q' to quit." << endl;
            continue;
        }
        // Try to move the player, if invalid move, ask for input again
        if (!player->move(direction,enemies,enemyCount,walls,wallCount,width,height)) {
            cout << escapeCodeBase("91") << "Invalid move." << colourReset() << endl;
            direction = -1;
            continue;
        } else {
            turns++;
            return true;
        }
    } while (direction == -1);
    return true;
}

bool Level::enemiesMove() {
    // Call enemy move functions, returns false for game over
	for (int i = 0; i < enemyCount; i++) {
        if (enemies[i]->isAlive()) {
            if (enemies[i]->move(walls, wallCount, enemies, enemyCount, player, width, height)) {
                return false;
            }
        }
	}
    return true;
}

int Level::getTurns() {
    return turns;
}
