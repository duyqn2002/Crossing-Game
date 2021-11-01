#include "CANIMAL.h"

void CANIMAL::ResetPos() {
	if (mCurrPos.getX() < mLeft - mWidth)
		mCurrPos.setX(mRight + mWidth);

	if (mCurrPos.getX() > mRight + mWidth)
		mCurrPos.setX(mLeft - mWidth);
}

void CANIMAL::setXY(int x, int y) {
	mCurrPos.setXY(x, y);
}

void CANIMAL::setLimit(int leftX, int rightY) {
	mLeft = leftX;
	mRight = rightY;
}

void CANIMAL::setSpeed(int speed) {
	mSpeed = speed;
}

int CANIMAL::getX() const {
	return mCurrPos.getX();
}

int CANIMAL::getY() const {
	return mCurrPos.getY();
}

int CANIMAL::Width() const {
	return mWidth;
}
int CANIMAL::Height() const {
	return mHeight;
}

void CANIMAL::Move(int deltaX, int deltaY) {
	mCurrPos.moveXY(deltaX, deltaY);
}

void CANIMAL::updatePos() {
	Move(mSpeed, 0);
	ResetPos();
}

void CANIMAL::drawVehicle(const Console& console) const {
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();

	int startPos = 0;
	int nChar = 0;

	if (mSpeed < 0) {
	}
	else {
	}
}