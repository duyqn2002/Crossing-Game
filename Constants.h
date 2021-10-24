#ifndef CONSTANTS_H
#define CONSTANTS_H

// Default setting for game
#define TOP_LEFT_X 0
#define TOP_LEFT_Y 0
#define SCALE_X 1
#define SCALE_Y 0.65

// Constant color for game
#define DEFAULT_COLOR COLOR::WHITE
#define PLAYING_AREA_COLOR COLOR::GREEN
#define LANE_COLOR COLOR::CYAN
#define PEOPLE_COLOR COLOR::RED
#define TRUCK_COLOR COLOR::WHITE	

// Border char
#define TOP_LEFT_CORNER char(201)
#define TOP_RIGHT_CORNER char(187)
#define BOTTOM_LEFT_CORNER char(200)
#define BOTTOM_RIGHT_CORNER char(188)
#define HORIZONTAL_OUTLINE char(205)
#define VERTICAL_OUTLINE char(186)

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

#endif // !CONSTANTS_H
