#ifndef CANIMAL_H
#define CANIMAL_H

#include "CPOINT2D.h"
#include "Console.h"

class CANIMAL {
protected:
	// Current position
	CPOINT2D mCurrPos;

	// Width and height of vehicle
	int mHeight = 0;
	int mWidth = 0;

	// Limit left and right X
	int mLeft = 0;
	int mRight = 0;

	int mSpeed;
	Texture mAnimalLeftForm;
	Texture mAnimalRightForm;

	COLOUR mAnimalColour = DEFAULT_COLOUR;
public:
	CANIMAL() = default;
	virtual ~CANIMAL() = default;

	void ResetPos();

	// Setter
	void setXY(int, int);
	void setLimit(int, int);
	void setSpeed(int);

	// Getter
	int getX() const;
	int getY() const;
	int Width() const;
	int Height() const;

	virtual void Move(int, int);
	virtual void updatePos();

	// Render method
	virtual void drawVehicle(const Console&) const;
};

#endif // CANIMAL_H
