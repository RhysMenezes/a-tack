#ifndef _PRINT_UTILS_H
#define _PRINT_UTILS_H
#include <string>
#include <termios.h>

// Declare a number of convenience functions for formatting output strings

// Clear the screen
void clearScreen();

// Adds the required prefix and suffix for an ANSI escape code sequence
std::string escapeCodeBase(std::string code);

//only accept single characters as input
void singleChar();

//accept strings as input
void multiChar();

// Resets formatting to normal
std::string colourReset();

//gets the single character entered by the user
std::string getSingleChar();

// Make string output bold
std::string colourBold();

#endif
