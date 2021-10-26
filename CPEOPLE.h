#include "CVEHICLE.h"
#include "CANIMAL.h"

#ifndef CPEOPLE_H
#define CPEOPLE_H

#include <string>
#include <iostream>
#include <sstream>
#include "HelpFunctions.h"

using namespace std;

class CPEOPLE{
	CPOINT2D mCurrPos;
	CPOINT2D mTopLeft, mBottomRight; // Limit zone
	int mHeight, mWidth;
	bool mState; // State of alive
	string mPeopleRightForm;
	string mPeopleLeftForm;
	DIRECTION mMovingDirection;

public:
	CPEOPLE();
	void setXY(int, int);
	void setLimitZone(CPOINT2D, CPOINT2D);

	int getHeight() const;
	int getWidth() const;

	// Moving function
	void Up(int);
	void Left(int);
	void Right(int);
	void Down(int);
	void Move(DIRECTION);

	// Check impact
	bool isImpact(const CVEHICLE*&);
	bool isImpact(const CANIMAL*&);

	// Handle the event
	bool isFinish();
	bool isDead();
	bool isHitLimit(DIRECTION);

	// Render people function
	void eraseTraceOfPeople();
	void drawPeople() const;
};

#endif // CPEOPLE_H
