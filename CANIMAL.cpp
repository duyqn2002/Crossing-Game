#include "CANIMAL.h"

CANIMAL* CANIMAL::addSample(CANIMAL* animal) {
	if (animal == nullptr)
		return nullptr;
	m_vecSampleObjects.push_back(animal);
	return animal;
}

CANIMAL* CANIMAL::createObject(const string& className) {
	if (className == "")
		return nullptr;

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

void CANIMAL::setLimit(int leftX, int rightY) {
	mLeft = leftX;
	mRight = rightY;
}

void CANIMAL::setSpeed(double speed) {
	mSpeed = speed;

	toggleForm();
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

int CANIMAL::getLeft() const {
	return mLeft;
}

int CANIMAL::getRight() const {
	return mRight;
}

int CANIMAL::getSpeed() const {
	return mSpeed;
}

bool CANIMAL::isImpact(const CANIMAL& other) const {
	int thisX = this->getX();
	int otherX = other.getX();

	if (thisX == otherX)
		return true;

	if (thisX > otherX && thisX < otherX + mWidth)
		return true;

	if (thisX < otherX && thisX + mWidth > otherX)
		return true;

	return false;
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
		mCurrPos.setX(mRight);

	if (mCurrPos.getX() > mRight)
		mCurrPos.setX(mLeft - mWidth);
}

void CANIMAL::updatePos() {
	Move(mSpeed, 0);
	resetPos();
}

void CANIMAL::drawAnimal(const Console& console) const {
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();

	vector<string> form = mCurrAnimalForm->GetTexture();

	for (const auto& line : form) {
		for (const auto& c : line) {
			if (x > mLeft && x < mRight) {
				// If inside the playing zone then draw it
				console.DrawPixels(x, y, c, mAnimalColour);
			}

			x++;
		}
		x = mCurrPos.getX();
		y++;
	}
}