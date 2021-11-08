#include "CVEHICLE.h"

CVEHICLE* CVEHICLE::addSample(CVEHICLE* vehicle) {
	if (vehicle == nullptr)
		return nullptr;
	m_vecSampleObjects.push_back(vehicle);
	return vehicle;
}

CVEHICLE* CVEHICLE::createObject(const string& className) {
	if (className == "")
		return nullptr;

	for (auto object : m_vecSampleObjects) {
		if (object != nullptr && object->className() == className) {
			return object->Clone();
		}
	}

	return nullptr;
}

void CVEHICLE::setX(int x) {
	mCurrPos.setX(x);
}

void CVEHICLE::setY(int y) {
	mCurrPos.setY(y);
}

void CVEHICLE::setXY(int x, int y) {
	mCurrPos.setXY(x, y);
}

void CVEHICLE::setLimit(int left, int right) {
	mLeft = left;
	mRight = right;
}

void CVEHICLE::setSpeed(double speed) {
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

int CVEHICLE::getLeft() const {
	return mLeft;
}

int CVEHICLE::getRight() const {
	return mRight;
}

int CVEHICLE::getSpeed() const {
	return mSpeed;
}

bool CVEHICLE::isImpact(const CVEHICLE& other) const {
	int thisX = this->getX();
	int otherX = other.getX();

	if (thisX == otherX)
		return true;

	if (thisX > otherX && thisX < otherX + mWidth )
		return true;

	if (thisX < otherX && thisX + mWidth > otherX )
		return true;

	return false;
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
				console.DrawPixels(x, y, c, mVehicleColour);
			}

			x++;
		}
		x = mCurrPos.getX();
		y++;
	}
}