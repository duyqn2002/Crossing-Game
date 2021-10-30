#include "CVEHICLE.h"

void CVEHICLE::reset() {
	mCurrPos.setX(mStartPosX);
}

void CVEHICLE::setXY(int x, int y) {
	mCurrPos.setXY(x, y);
}

void CVEHICLE::setStartPosX(int startX) {	
	mStartPosX = startX;
	mCurrPos.setX(startX);
}

void CVEHICLE::setLeft(int srcX) {
	mLeft = srcX;
}

void CVEHICLE::setRight(int desX) {
	mRight = desX;
}

int CVEHICLE::getX() const {
	return mCurrPos.getX();
}

int CVEHICLE::getY() const {
	return mCurrPos.getY();
}

int CVEHICLE::Width() const {
	return mWidth;
}
int CVEHICLE::Height() const {
	return mHeight;
}

void CVEHICLE::Move(int deltaX, int deltaY) {
	mCurrPos.moveXY(deltaX, deltaY);
}

	void CVEHICLE::eraseVehicleHead() const {
		int line = 0;
		int x = mCurrPos.getX();
		int y = mCurrPos.getY();
		while (line < mHeight) {
			GotoXY(x, y + line++);
			cout << " ";
		}
	}

	void CVEHICLE::eraseVehicleTail() const {
		int line = 0;
		int x = mCurrPos.getX() + mWidth;
		int y = mCurrPos.getY();
		while (line < mHeight) {
			GotoXY(x, y + line++);
			cout << " ";
		}
	}

void CVEHICLE::eraseOldVehicle() const {
	switch (mMovingDirection)
	{
	case DIRECTION::LEFT:
		eraseVehicleTail();
		break;
	case DIRECTION::RIGHT:
		eraseVehicleHead();
		break;
	default:
		return;
	}
}

void CVEHICLE::drawVehicle() const {
	// If the truck in playing zone then draw it
	if (isOutSide() == true)
		return;

	int startChar = 0;
	int nChar = 0;
	stringstream sstream;
	string tempStr = "";
	int line = 0;
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();

	if (x < mLeft) {
		startChar = mLeft + 1 - x;
		nChar = mWidth - startChar;
	}
	else {
		if (x + mWidth >= mRight) {
			startChar = 0;
			nChar = mRight - x;
		}
		else {
			nChar = mWidth;
		}
	}

	if (mMovingDirection == DIRECTION::LEFT) {
		sstream << mVehicleLeftForm;
	}
	else {
		sstream << mVehicleRightForm;
	}

	TextColor(mVehicleColour);
	while (getline(sstream, tempStr, '\n')) {
		GotoXY(x + startChar, y + line++);
		cout << tempStr.substr(startChar, nChar);
	}
}

void CVEHICLE::updatePos(int deltaX) {
	// Before update position, erase the old trace of vehicle
	eraseOldVehicle();

	switch (mMovingDirection)
	{
	case DIRECTION::LEFT:
		Move(-deltaX, 0);
		break;
	case DIRECTION::RIGHT:
		if (mCurrPos.getX() > mRight + 10) {
			reset();
		}
		Move(deltaX, 0);
		break;
	default:
		return;
	}
}

bool CVEHICLE::isOutSide() const {
	bool isOutSide = false;
	int x = mCurrPos.getX();

	switch (mMovingDirection)
	{
	case DIRECTION::LEFT:
		if (x + mWidth >= mLeft || x <= mRight)
			isOutSide = true;
		break;
	case DIRECTION::RIGHT:
		if (x + mWidth <= mLeft || x  >= mRight)
			isOutSide = true;
		break;
	default:
		break;
	}

	return isOutSide;
}