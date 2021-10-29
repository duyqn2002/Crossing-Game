#ifndef CVEHICLE_H
#define CVEHICLE_H

#include "HelpFunctions.h"
#include "CPOINT2D.h"

class CVEHICLE {
protected:
	CPOINT2D mCurrPos;
	int mStartPosX = 0;

	int mLeft = 0;
	int mRight = 0;

	int mHeight = 0;
	int mWidth = 0;
	DIRECTION mMovingDirection;
	string mVehicleLeftForm;
	string mVehicleRightForm;
	COLOUR mVehicleColour = DEFAULT_COLOUR;
public:
	CVEHICLE() = default;
	virtual ~CVEHICLE() = default;
	void reset();

	void setXY(int, int);
	void setStartPosX(int);
	void setLeft(int);
	void setRight(int);

	int getX() const;
	int getY() const;

	int Width() const;
	int Height() const;

	virtual void Move(int, int);
	virtual void eraseVehicleHead() const;
	virtual void eraseVehicleTail() const;
	virtual void eraseOldVehicle() const;
	virtual void drawVehicle() const;

	virtual bool isOutSide() const;
	virtual void updatePos(int);
};

#endif // CVEHICLE_H
