#include "CVEHICLE.h"

void CVEHICLE::ResetPos() {
	if (mCurrPos.getX() < mLeft - mWidth)
		mCurrPos.setX(mRight + mWidth);

	if (mCurrPos.getX() > mRight + mWidth)
		mCurrPos.setX(mLeft - mWidth);
}

void CVEHICLE::setXY(int x, int y) {
	mCurrPos.setXY(x, y);
}

void CVEHICLE::setLimit(int leftX, int rightY) {
	mLeft = leftX;
	mRight = rightY;
}

void CVEHICLE::setSpeed(int speed) {
	mSpeed = speed;
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

void CVEHICLE::updatePos() {
	Move(mSpeed, 0);
	ResetPos();
}

void CVEHICLE::drawVehicle(const Console& console) const {
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();

	int startPos = 0;
	int nChar = mWidth;

	vector<string> currForm = (mSpeed < 0) ? mVehicleLeftForm.GetTexture() : mVehicleRightForm.GetTexture();

	for (const auto& line : currForm) {
		for (const auto& c : line) {
			console.Draw(x, y, c, mVehicleColour);
			x++;
		}
		x = mCurrPos.getX();
		y++;
	}
}