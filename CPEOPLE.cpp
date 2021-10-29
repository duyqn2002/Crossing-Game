#include "CPEOPLE.h"

CPEOPLE::CPEOPLE() {
	mState = true;

	mPeopleRightForm ="~o/\n"
					  "/| \n"
					  "/ \\";

	mPeopleLeftForm = "\\o~\n"
					  " |\\\n"
					  "/ \\";

	mHeight = GetHeightAsciiArt(mPeopleLeftForm);
	mWidth = GetWidthAsciiArt(mPeopleLeftForm);

	mMovingDirection = RandomInt(2,0) ? DIRECTION::LEFT : DIRECTION::RIGHT; // Randomly start direction
}

void CPEOPLE::setXY(int x, int y) {
	mCurrPos.setX(x);
	mCurrPos.setY(y);
}

void CPEOPLE::setLimitZone(CPOINT2D topLeft, CPOINT2D bottomRight) {
	mTopLeft = topLeft;
	mBottomRight = bottomRight;
}

int CPEOPLE::getHeight() const{
	return mHeight;
}

int CPEOPLE::getWidth() const{
	return mWidth;
}

void CPEOPLE::Clip(int& x, int& y) {
	if (x <= mTopLeft.getX())
		x = mTopLeft.getX() + 1;

	if (x >= mBottomRight.getY())
		x = mBottomRight.getX() - mWidth;

	if (y < mTopLeft.getY())
		y = mTopLeft.getY() + 1;

	if (y >= mBottomRight.getY())
		y = mBottomRight.getY() - mHeight;
}

void CPEOPLE::Up(int delta) {
	mCurrPos.moveY(-delta);
	mMovingDirection = DIRECTION::UP;
}

void CPEOPLE::Left(int delta) {
	mCurrPos.moveX(-delta);
	mMovingDirection = DIRECTION::LEFT;
}

void CPEOPLE::Right(int delta) {
	mCurrPos.moveX(delta);
	mMovingDirection = DIRECTION::RIGHT;
}

void CPEOPLE::Down(int delta) {
	mCurrPos.moveY(delta);
	mMovingDirection = DIRECTION::DOWN;
}

void CPEOPLE::Move(DIRECTION direction, int delta) {

	switch (direction){
		case DIRECTION::UP:
					Up(delta);
					break;

		case DIRECTION::DOWN:
					Down(delta);
					break;

		case DIRECTION::LEFT:
					Left(mWidth);
					break;

		case DIRECTION::RIGHT:
					Right(mWidth);
					break;
	}
}

bool CPEOPLE::isImpact(const vector<CVEHICLE>& allVehicles) {
	return false;
}

bool CPEOPLE::isImpact(const vector<CANIMAL>&) {
	return false;
}

bool  CPEOPLE::isFinish() {
	if (mCurrPos.getY() == mTopLeft.getY() - 1)
		return true;

	return false;
}

bool  CPEOPLE::isDead() {
	/*if (mState == false)
		return true;
	return false;*/
	return !mState;
}

bool CPEOPLE::isHitLimit(DIRECTION direction) {
	bool isOutSide = false;
	int maxX, minX;
	int maxY, minY;
	int currX, currY;

	minX = mTopLeft.getX() + 1;
	minY = mTopLeft.getY() + 1;

	maxX = mBottomRight.getX() - mWidth;
	maxY = mBottomRight.getY() - mHeight;

	currX = mCurrPos.getX();
	currY = mCurrPos.getY();

	switch (direction)
	{
	case DIRECTION::UP:
		if (currY == minY)
			isOutSide = true;
		break;
	case DIRECTION::DOWN:
		if (currY == maxY)
			isOutSide = true;
		break;
	case DIRECTION::LEFT:
		if (currX == minX)
			isOutSide = true;
		break;
	case DIRECTION::RIGHT:
		if (currX == maxX)
			isOutSide = true;
		break;
	}

	return isOutSide;
}


void CPEOPLE::eraseTraceOfPeople() {
	int index = 0;
	string line = "";
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();

	while (index++ < mWidth) {
		line += " ";
	}

	index = 0;
	while (index < mHeight) {
		GotoXY(x, y + index++);
		cout << line;
	}
}

void CPEOPLE::drawPeople() const {
	stringstream sstream;
	if (mMovingDirection == DIRECTION::LEFT) {
		sstream << mPeopleLeftForm;
	}
	else {
		sstream << mPeopleRightForm;
	}

	string tempStr = "";
	int line = 0;
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();
	TextColor(PEOPLE_COLOUR);

	while (getline(sstream, tempStr, '\n')) {
		GotoXY(x, y + line++);
		/*for (int i = 0; i < mWidth; i++) {
			if (tempStr[i] != ' ' && tempStr[i] != '\n') {
				TextColor((COLOUR)170);
				cout << " ";
			}
		}*/
		cout << tempStr;
	}
}
