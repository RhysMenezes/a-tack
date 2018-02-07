#include "PrintUtils.h"
#include <stdlib.h>
#include <string>

void clearScreen() {
    // Use preproccesor for different clear commands on differents systems
    #ifdef _WIN32
    system("cls");
    #else
    system("clear");
    #endif
}

std::string escapeCodeBase(std::string code) {
    return "\033["+code+"m";
}

std::string colourReset() {
    return escapeCodeBase("0") ;
}

std::string colourBold() {
    return escapeCodeBase("1");
}
