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
constexpr short WINDOW_BUFFER_HEIGHT = 50;
constexpr short WINDOW_BUFFER_WIDTH = 150;
constexpr short FONT_HEIGHT = 12;
constexpr short FONT_WIDTH = 12;

constexpr short LANE_SIZE = 4;
constexpr short MAX_VEHICLES = 3;
constexpr short MAX_ANIMALS = 3;

// Position of top left corner of playing area
constexpr short TOP_LEFT_X = 1;
constexpr short TOP_LEFT_Y = 0;

// Scale of the playing area
constexpr float SCALE_X = 0.75f;
constexpr float SCALE_Y = 1;

// Constant color for game
#define DEFAULT_COLOUR COLOUR::WHITE
#define PLAYING_AREA_COLOUR COLOUR::CYAN_BG
#define LANE_COLOUR COLOUR::CYAN
#define PEOPLE_COLOUR COLOUR::RED
#define TRUCK_COLOUR COLOUR::PINK
#define CAR_COLOUR COLOUR::CYAN
#define DOG_COLOUR   COLOUR::GREEN
#define BIRD_COLOUR  COLOUR:: RED

enum class KEY {
	UP = 'W',
	DOWN = 'S',
	LEFT = 'A',
	RIGHT = 'D',
	SPACE = ' ',

	RETURN = '\r',
	ESC = (char)27,

	YES = 'Y',
	NO = 'N',
	SAVE_GAME = 'L',
	LOAD_GAME = 'T',
	PAUSE_GAME = 'P',

	NULL_CHAR = '\0',
};

enum class COLOUR {
	GREEN = 10,
	CYAN = 11,
	RED = 12,
	PINK = 13,
	WHITE = 15,

	RED_BG = 204,
	GREEN_BG = 170,
	CYAN_BG = 187,
};

enum class LEVEL {
	EASY = 1,
	MEDIUM = 2,
	HARD = 3
};

enum class ENEMY {
	CTRUCK,
	CCAR,
	CDOG,
	CBIRD,
	NO_ENEMY
};

#endif // CONSTANTS_H
