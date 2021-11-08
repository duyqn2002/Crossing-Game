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
constexpr short MAX_LANE = 12;
constexpr short LANE_SIZE = 4;
constexpr short MAX_VEHICLE = 3;
constexpr short MAX_ANIMAL = 3;

// Position of top left corner of playing area
constexpr short TOP_LEFT_X = 0;
constexpr short TOP_LEFT_Y = 0;

// Scale of the playing area
constexpr float SCALE_X = 0.75f;
constexpr float SCALE_Y = 1;

// Border char
constexpr char TOP_LEFT_CORNER = char(201);
constexpr char TOP_RIGHT_CORNER = char(187);
constexpr char BOTTOM_LEFT_CORNER = char(200);
constexpr char BOTTOM_RIGHT_CORNER = char(188);
constexpr char HORIZONTAL_OUTLINE = char(205);
constexpr char VERTICAL_OUTLINE = char(186);
constexpr char LANE_ROAD = char(196);

// Constant color for game
#define DEFAULT_COLOUR COLOUR::WHITE
#define PLAYING_AREA_COLOUR COLOUR::GREEN_BG
#define LANE_COLOUR COLOUR::CYAN
#define PEOPLE_COLOUR COLOUR::RED
#define TRUCK_COLOUR COLOUR::PINK
#define CAR_COLOUR COLOUR::CYAN
#define DOG_COLOUR   COLOUR::GREEN
#define BIRD_COLOUR  COLOUR:: RED

// Macro
#define INIT_BASE(BASE) std::vector<BASE*> BASE::m_vecSampleObjects;
#define INIT_MEMBER(BASE_CLASS,CHILD_CLASS) static BASE_CLASS* BootTrapObject##CHILD_CLASS
#define INIT_OBJECT(BASE_CLASS,CHILD_CLASS) BASE_CLASS* CHILD_CLASS::BootTrapObject##CHILD_CLASS = BASE_CLASS::addSample(new CHILD_CLASS())
#define INIT_METHOD(BASE_CLASS,CHILD_CLASS) virtual string className() { return #CHILD_CLASS;} \
									virtual BASE_CLASS* Clone() { return new CHILD_CLASS(*this);}


enum class DIRECTION : char {
	UP = 'W',
	DOWN = 'S',
	LEFT = 'A',
	RIGHT = 'D',
	STAND_STILL = ' '
};

enum class COLOUR : int {
	GREEN = 10,
	CYAN = 11,
	RED = 12,
	PINK = 13,
	WHITE = 15,

	GREEN_BG = 170,
};

enum class LEVEL : int {
	EASY = 1,
	MEDIUM = 2,
	HARD = 3
};

enum class KEY {
	// Mot so nut bam nhu esc, pause game
};

#endif // CONSTANTS_H
