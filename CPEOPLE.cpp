#include "CPEOPLE.h"

CPEOPLE::CPEOPLE() {
	this->mState = true;

	this->mPeopleRightForm = "~o/\n"
						     "/| \n"
						     "/ \\";

	this->mPeopleLeftForm = "\\o~\n" 
					        " |\\\n" 
		                    "/ \\";

	this->mHeight = GetHeightAsciiArt(this->mPeopleLeftForm);
	this->mWidth = GetWidthAsciiArt(this->mPeopleLeftForm);

	this->mMovingDirection = RandomInt(2,0) ? DIRECTION::LEFT : DIRECTION::RIGHT; // Randomly start direction
}

void CPEOPLE::setXY(int x, int y) {
	this->mCurrPos.setX(x);
	this->mCurrPos.setY(y);
}

void CPEOPLE::setLimitZone(CPOINT2D topLeft, CPOINT2D bottomRight) {
	this->mTopLeft = topLeft;
	this->mBottomRight = bottomRight;
}

int CPEOPLE::getHeight() const{
	return this->mHeight;
}

int CPEOPLE::getWidth() const{
	return this->mWidth;
}

void CPEOPLE::Up(int delta) {
	this->mCurrPos.moveY(-delta);
	this->mMovingDirection = DIRECTION::UP;
}

void CPEOPLE::Left(int delta) {
	this->mCurrPos.moveX(-delta);
	this->mMovingDirection = DIRECTION::LEFT;
}

void CPEOPLE::Right(int delta) {
	this->mCurrPos.moveX(delta);
	this->mMovingDirection = DIRECTION::RIGHT;
}

void CPEOPLE::Down(int delta) {
	this->mCurrPos.moveY(delta);
	this->mMovingDirection = DIRECTION::DOWN;
}

void CPEOPLE::Move(DIRECTION direction) {
	this->eraseTraceOfPeople();
	switch (direction)
	{
	case DIRECTION::UP:
				this->Up(4);
				break;
	case DIRECTION::DOWN:
				this->Down(1);
				break;
	case DIRECTION::LEFT:
				this->Left(1);
				break;
	case DIRECTION::RIGHT:
				this->Right(1);
				break;
	
	}
}

bool CPEOPLE::isImpact(const CVEHICLE*&) {
	return true;
}

bool CPEOPLE::isImpact(const CANIMAL*&) {
	return true;
}

bool  CPEOPLE::isFinish() {
	if (this->mCurrPos.getY() == this->mTopLeft.getY() - 1)
		return true;

	return false;
}

bool  CPEOPLE::isDead() {
	if (mState == false)
		return true;
	return false;
}

bool CPEOPLE::isHitLimit(DIRECTION direction) {
	bool isOutSide = false;
	int maxX, minX;
	int maxY, minY;
	int currX, currY;

	minX = this->mTopLeft.getX() + 1;
	minY = this->mTopLeft.getY() + 1;

	maxX = this->mBottomRight.getX() - this->mWidth;
	maxY = this->mBottomRight.getY() - this->mHeight;

	currX = this->mCurrPos.getX();
	currY = this->mCurrPos.getY();

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
	int x = this->mCurrPos.getX();
	int y = this->mCurrPos.getY();

	
	while (index++ < this->mWidth) {
		line += " ";
	}

	index = 0;
	while (index < this->mHeight) {
		GotoXY(x, y + index++);
		cout << line;
	}
}

void CPEOPLE::drawPeople() {
	stringstream sstream;
	if (this->mMovingDirection == DIRECTION::LEFT) {
		sstream << this->mPeopleLeftForm;
	}
	else {
		sstream << this->mPeopleRightForm;
	}

	string tempStr = "";
	int line = 0;
	int x = this->mCurrPos.getX();
	int y = this->mCurrPos.getY();
	TextColor(PEOPLE_COLOR);
	while (getline(sstream, tempStr, '\n')) {
		GotoXY(x, y + line++);
		cout << tempStr;
	}
}
