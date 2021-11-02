#include "CVEHICLE.h"

void CVEHICLE::setXY(int x, int y) {
	mCurrPos.setXY(x, y);
}

void CVEHICLE::setLimit(int left, int right) {
	mLeft = left;
	mRight = right;
}

void CVEHICLE::setSpeed(int speed) {
	mSpeed = speed;

	toggleForm();
}

void CVEHICLE::setColour(COLOUR color) {
	mVehicleColour = color;
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

void CVEHICLE::toggleForm() {
	if (mSpeed < 0) {
		mCurrVehicleForm = &mVehicleLeftForm;
	}
	else {
		mCurrVehicleForm = &mVehicleRightForm;
	}

	mHeight = mCurrVehicleForm->Height();
	mWidth = mCurrVehicleForm->Width();
}

void CVEHICLE::Move(int deltaX, int deltaY) {
	mCurrPos.moveXY(deltaX, deltaY);
}

void CVEHICLE::resetPos() {
	if (mCurrPos.getX() < mLeft - mWidth)
		mCurrPos.setX(mRight);

	if (mCurrPos.getX() > mRight)
		mCurrPos.setX(mLeft - mWidth);
}

void CVEHICLE::updatePos() {
	Move(mSpeed, 0);
	resetPos();
}

void CVEHICLE::drawVehicle(const Console& console) const {
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();

	vector<string> form = mCurrVehicleForm->GetTexture();

	for (const auto& line : form) {
		for (const auto& c : line) {
			if (x > mLeft && x < mRight) {
				// If inside the playing zone then draw it
				console.Draw(x, y, c, mVehicleColour);
			}
			x++;
		}
		x = mCurrPos.getX();
		y++;
	}
}