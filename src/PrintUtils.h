#ifndef _PRINT_UTILS_H
#define _PRINT_UTILS_H
#include <string>

// Declare a number of convenience functions for formatting output strings

// Clear the screen
void clearScreen();

// Adds the required prefix and suffix for an ANSI escape code sequence
std::string escapeCodeBase(std::string code);

// Resets formatting to normal
std::string colourReset();

// Make string output bold
std::string colourBold();

#endif
