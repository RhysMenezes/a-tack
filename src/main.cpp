#include "App.h"

int main() {
    // Create an instance of App and let it run
    App *application = new App();
    application->run();
    delete application;
    
    return 0;
}
