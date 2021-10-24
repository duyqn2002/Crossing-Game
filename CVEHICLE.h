#ifndef CVEHICLE_H
#define CVEHICLE_H
#include "HelpFunctions.h"
#include "CPOINT2D.h"

class CVEHICLE {
protected:
	CPOINT2D mCurrPos;
	int mSrcX, mDesX;
	int mHeight, mWidth; 
	DIRECTION mMovingDirection;
	string mVehicleLeftForm;
	string mVehicleRightForm;
public:
	CVEHICLE();
	virtual ~CVEHICLE();
	virtual char getName() const { return 'A'; }
	void setXY(int,int);
	virtual void Move(int, int);
	virtual void eraseVehicleHead();
	virtual void eraseVehicleTail();
	virtual void erase();
	virtual void drawVehicle();
	bool isHitLimit() const;
	void updatePos(int);
};

#endif // CVEHICLE_H

