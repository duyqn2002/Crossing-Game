#ifndef ENEMY_H
#define ENEMY_H

#include "Console.h"

class Movable {
public:
	Movable() {};
	virtual ~Movable() {};
	virtual Movable* Clone() = 0;

	// Setter
	virtual void setXY(int, int) = 0;
	virtual void setColour(COLOUR) = 0;

	// Getter
	virtual int getX() const = 0;
	virtual int getY() const = 0;
	virtual int Width() const = 0;
	virtual int Height() const = 0;

	// Update method
	virtual void toggleForm(int) = 0;
	virtual void Move(int, int) = 0;

	// Render method
	virtual void drawToConsole(Console&, int, int) = 0;
};

#endif // ENEMY_H
