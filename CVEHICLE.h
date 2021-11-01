#ifndef CVEHICLE_H
#define CVEHICLE_H

#include "HelpFunctions.h"
#include "CPOINT2D.h"
#include "Console.h"

class CVEHICLE {
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
	Texture mVehicleLeftForm;
	Texture mVehicleRightForm;

	COLOUR mVehicleColour = DEFAULT_COLOUR;
public:
	CVEHICLE() = default;
	virtual ~CVEHICLE() = default;

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

#endif // CVEHICLE_H
