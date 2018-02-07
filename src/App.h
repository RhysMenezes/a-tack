#ifndef _APP_H
#define _APP_H
#include "Game.h"
#include "Level.h"

// App
// Manages game objects, level selections and overall program strucutre
class App {
public:
    App();
    ~App();
    // Runs application, returns on termination
    void run();
private:
    // Shows titlescreen
    void showTitle();
    // Show quit message
    void quit();
    // Show help and information about the game
    void showHelp();
    // Provides dialog to select level
    Level* selectLevel();
    // Determines if application should continue running. If set to false, application will terminate when next asking for level
    bool running;
};

#endif
