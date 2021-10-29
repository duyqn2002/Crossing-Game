#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include "Constants.h"

void ConstructConsole(int width, int height, int fontw, int fonth);
void GotoXY(int x, int y);

int GetHeightConsoleWindowBuffer();
int GetWidthConsoleWindowBuffer();

int GetWidthAsciiArt(string);
int GetHeightAsciiArt(string);

int RandomInt(int, int);

void TextColor(COLOUR);


#endif // HELPFUNCTIONS_H
