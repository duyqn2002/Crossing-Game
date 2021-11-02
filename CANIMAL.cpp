#include "CANIMAL.h"

void CANIMAL::setXY(int x, int y) {
	mCurrPos.setXY(x, y);
}

void CANIMAL::setLimit(int leftX, int rightY) {
	mLeft = leftX;
	mRight = rightY;
}

void CANIMAL::setSpeed(int speed) {
	mSpeed = speed;

	toggleForm();
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

void CANIMAL::toggleForm() {
	if (mSpeed < 0) {
		mCurrAnimalForm = &mAnimalLeftForm;
	}
	else {
		mCurrAnimalForm = &mAnimalRightForm;
	}

	mHeight = mCurrAnimalForm->Height();
	mWidth = mCurrAnimalForm->Width();
}

void CANIMAL::Move(int deltaX, int deltaY) {
	mCurrPos.moveXY(deltaX, deltaY);
}

void CANIMAL::resetPos() {
	if (mCurrPos.getX() < mLeft - mWidth)
		mCurrPos.setX(mRight + mWidth);

	if (mCurrPos.getX() > mRight + mWidth)
		mCurrPos.setX(mLeft - mWidth);
}

void CANIMAL::updatePos() {
	Move(mSpeed, 0);
	resetPos();
}

void CANIMAL::drawVehicle(const Console& console) const {
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();

	vector<string> form = mCurrAnimalForm->GetTexture();

	for (const auto& line : form) {
		for (const auto& c : line) {
			if (x > mLeft && x < mRight) {
				// If inside the playing zone then draw it
				console.Draw(x, y, c, mAnimalColour);
			}
			x++;
		}
		x = mCurrPos.getX();
		y++;
	}
}