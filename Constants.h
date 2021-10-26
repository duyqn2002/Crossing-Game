#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <Windows.h>
#include <string>
#include <sstream>
#include <iostream>
#include <random>
#include <thread>
#include <fstream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include <vector>

using namespace std;

// Default setting for game
constexpr int WINDOW_HEIGHT = 700;
constexpr int WINDOW_WIDTH = 980;
constexpr short MAX_LANE = 7;
constexpr int GAP = WINDOW_HEIGHT / MAX_LANE;

// Position of top left corner of playing area
constexpr short TOP_LEFT_X = 0;
constexpr short TOP_LEFT_Y = 0;

// Scale of the playing area
constexpr float SCALE_X = 1;
constexpr float SCALE_Y = 0.8;

// Border char
constexpr char TOP_LEFT_CORNER = char(201);
constexpr char TOP_RIGHT_CORNER = char(187);
constexpr char BOTTOM_LEFT_CORNER = char(200);
constexpr char BOTTOM_RIGHT_CORNER = char(188);
constexpr char HORIZONTAL_OUTLINE = char(205);
constexpr char VERTICAL_OUTLINE = char(186);
constexpr char LANE_ROAD = char(196);

// Constant color for game
#define DEFAULT_COLOR COLOR::WHITE
#define PLAYING_AREA_COLOR COLOR::GREEN
#define LANE_COLOR COLOR::CYAN
#define PEOPLE_COLOR COLOR::RED
#define TRUCK_COLOR COLOR::WHITE

enum class DIRECTION : char {
	UP = 'W',
	DOWN = 'S',
	LEFT = 'A',
	RIGHT = 'D'
};

enum class COLOR : int {
	GREEN = 10,
	CYAN = 11,
	RED = 12,
	WHITE = 15,
};

enum class Level {
	EASY,
	MEDIUM,
	HARD
};

#endif // CONSTANTS_H
