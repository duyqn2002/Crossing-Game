#ifndef CVEHICLE_H
#define CVEHICLE_H

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

	// Speed of vehicle
	int mSpeed;

	// Vehicle form
	Texture mVehicleLeftForm;
	Texture mVehicleRightForm;
	Texture* mCurrVehicleForm;

	// Color for vehicle
	COLOUR mVehicleColour = DEFAULT_COLOUR;
public:
	CVEHICLE() = default;
	virtual ~CVEHICLE() = default;

	// Setter
	void setXY(int, int);
	void setLimit(int, int);
	void setSpeed(int);
	void setColour(COLOUR);

	// Getter
	int getX() const;
	int getY() const;
	int Width() const;
	int Height() const;

	virtual void toggleForm();
	virtual void Move(int, int);
	virtual void resetPos();
	virtual void updatePos();

	// Render method
	virtual void drawVehicle(const Console&) const;
};

#endif // CVEHICLE_H
