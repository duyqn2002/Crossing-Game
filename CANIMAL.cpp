#include"CANIMAL.h"

void CANIMAL::reset()
{
	mCurrPos.setX(mStartPosX);

}

void CANIMAL::setXY(int x,int y)
{
	mCurrPos.setXY(x, y);
}

void CANIMAL::setStartPosX(int startX)
{
	mStartPosX = startX;
	mCurrPos.setX(startX);

}

void CANIMAL::setLeft(int srcX) {
	mLeft = srcX;
}

void CANIMAL::setRight(int desX) {
	mRight = desX;
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

void CANIMAL::eraseAnimalHead() const {
	int line = 0;
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();
	while (line < mHeight) {
		GotoXY(x, y + line++);
		cout << " ";
	}
}

void CANIMAL ::eraseAnimalTail() const {
	int line = 0;
	int x = mCurrPos.getX() + mWidth;
	int y = mCurrPos.getY();
	while (line < mHeight) {
		GotoXY(x, y + line++);
		cout << " ";
	}
}
void CANIMAL::eraseOldAnimal() const {
	switch (mMovingDirection)
	{
	case DIRECTION::LEFT:
		eraseAnimalTail();
		break;
	case DIRECTION::RIGHT:
		eraseAnimalHead();
		break;
	default:
		return;
	}
}

void CANIMAL::drawAnimal() const {
	// If the Animal in playing zone then draw it
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
		sstream << mAnimalLeftForm;
	}
	else {
		sstream << mAnimalRightForm;
	}

	TextColor(mAnimalColour);
	while (getline(sstream, tempStr, '\n')) {
		GotoXY(x + startChar, y + line++);
		cout << tempStr.substr(startChar, nChar);
	}
}

bool CANIMAL::isOutSide() const {
	bool isOutSide = false;
	int x = mCurrPos.getX();

	switch (mMovingDirection)
	{
	case DIRECTION::LEFT:
		if (x + mWidth >= mLeft || x <= mRight)
			isOutSide = true;
		break;
	case DIRECTION::RIGHT:
		if (x + mWidth <= mLeft || x >= mRight)
			isOutSide = true;
		break;
	default:
		break;
	}

	return isOutSide;
}

void CANIMAL::updatePos(int deltaX) {
	// Before update position, erase the old trace of vehicle
	eraseOldAnimal();

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

