#include <Windows.h>
#include <string>
#include <sstream>
#include <iostream>
#include <random>
#include "Constants.h"

using namespace std;

#ifndef HELPFUNCTIONS_H
#define HELPFUNCTIONS_H

void FixConsoleWindow();
void ResizeConsole(int, int);
void GotoXY(int , int);
void ShowCursorConsole(bool);

int GetHeightConsoleWindowBuffer();
int GetWidthConsoleWindowBuffer();

int GetWidthAsciiArt(string);
int GetHeightAsciiArt(string);

int RandomInt(int, int);

void TextColor(COLOR);
void deleteScreen();

#endif // HELPFUNCTIONS_H
