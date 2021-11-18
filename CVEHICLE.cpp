#include "CVEHICLE.h"

CVEHICLE* CVEHICLE::addSample(CVEHICLE* vehicle) {
	if (vehicle == nullptr)
		return nullptr;
	m_vecSampleObjects.push_back(vehicle);
	return vehicle;
}

CVEHICLE* CVEHICLE::createObject(const ENEMY& className) {
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

void CVEHICLE::toggleForm(int speed) {
	if (speed < 0) {
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

void CVEHICLE::drawToConsole(int leftLimit,int rightLimit,Console& console) {
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();

	vector<string> form = mCurrVehicleForm->getTexture();

	for (const auto& line : form) {
		for (const auto& c : line) {
			if (x > leftLimit && x < rightLimit) {
				// If inside the playing zone then draw it
				console.DrawPixels(x, y, c, mVehicleColour);
			}

			x++;
		}
		x = mCurrPos.getX();
		y++;
	}
}