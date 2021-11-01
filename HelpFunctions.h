#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

#include "Constants.h"

void GotoXY(int x, int y);
void SetConsoleGameTitle(string);
void GotoXY(int x, int y);

int GetWidthAsciiArt(const string&);
int GetHeightAsciiArt(const string&);

int RandomInt(int, int);
void TextColor(COLOUR);

#endif // HELPFUNCTIONS_H
