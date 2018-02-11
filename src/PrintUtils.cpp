#include "PrintUtils.h"
#include <stdlib.h>
#include <string>
#include <termios.h>
#include <unistd.h>

struct termios term;

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

void singleChar(){
    tcgetattr(STDIN_FILENO,&term);
    term.c_lflag &=~ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW,&term);
}

void multiChar(){
    tcgetattr(STDIN_FILENO,&term);
    term.c_lflag |= ICANON;
    tcsetattr(STDIN_FILENO, TCSANOW,&term);
}

std::string getSingleChar() {
    singleChar();
    char c = getchar();
    multiChar();
    std::string command = " ";
    command[0] = c;
    return command;
}
