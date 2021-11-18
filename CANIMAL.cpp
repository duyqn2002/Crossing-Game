#include "CANIMAL.h"

CANIMAL* CANIMAL::addSample(CANIMAL* animal) {
	if (animal == nullptr)
		return nullptr;
	m_vecSampleObjects.push_back(animal);
	return animal;
}

CANIMAL* CANIMAL::createObject(const ENEMY& className) {
	for (auto object : m_vecSampleObjects) {
		if (object != nullptr && object->className() == className) {
			return object->Clone();
		}
	}

	return nullptr;
}

void CANIMAL::setX(int x) {
	mCurrPos.setX(x);
}

void CANIMAL::setY(int y) {
	mCurrPos.setY(y);
}

void CANIMAL::setXY(int x, int y) {
	mCurrPos.setXY(x, y);
}

void CANIMAL::setColour(COLOUR color) {
	mAnimalColour = color;
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

void CANIMAL::toggleForm(int speed) {
	if (speed < 0) {
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

void CANIMAL::drawToConsole(int leftLimit,int rightLimit,Console& console) {
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();

	vector<string> form = mCurrAnimalForm->getTexture();

	for (const auto& line : form) {
		for (const auto& c : line) {
			if (x > leftLimit && x < rightLimit) {
				// If inside the playing zone then draw it
				console.DrawPixels(x, y, c, mAnimalColour);
			}

			x++;
		}
		x = mCurrPos.getX();
		y++;
	}
}