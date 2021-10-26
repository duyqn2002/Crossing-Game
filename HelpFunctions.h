#include "Constants.h"

#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

void FixConsoleWindow();
void ResizeConsoleAndCenterConsole(int, int);
void GotoXY(int , int);
void ShowCursorConsole(bool);

int GetHeightConsoleWindowBuffer();
int GetWidthConsoleWindowBuffer();

int GetWidthAsciiArt(string);
int GetHeightAsciiArt(string);

int RandomInt(int, int);

void TextColor(COLOR);
void DeleteScreen();

#endif // HELPFUNCTIONS_H
