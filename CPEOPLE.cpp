#include "CPEOPLE.h"

CPEOPLE::CPEOPLE() {
	mState = true;

	mPeopleRightForm = "~o/\n"
		"/| \n"
		"/ \\";

	mPeopleLeftForm = "\\o~\n"
					" |\\\n"
					"/ \\";

	mHeight = mPeopleLeftForm.Height();
	mWidth = mPeopleLeftForm.Width();

	mMovingDirection = RandomInt(2, 0) ? DIRECTION::LEFT : DIRECTION::RIGHT; // Randomly start direction
}

CPEOPLE::CPEOPLE(int x, int y) : CPEOPLE() {
	setXY(x, y);
}

CPEOPLE::CPEOPLE(int x, int y, CPOINT2D topLeft, CPOINT2D bottomRight) : CPEOPLE(x, y) {
	setLimitZone(topLeft, bottomRight);
}

void CPEOPLE::setXY(int x, int y) {
	mCurrPos.setX(x);
	mCurrPos.setY(y);
}

void CPEOPLE::setLimitZone(CPOINT2D topLeft, CPOINT2D bottomRight) {
	mTopLeft = topLeft;
	mBottomRight = bottomRight;
}

int CPEOPLE::Height() const {
	return mHeight;
}

int CPEOPLE::Width() const {
	return mWidth;
}

CPOINT2D CPEOPLE::GetPosition() const {
	return mCurrPos;
}

void CPEOPLE::Clip() {
	int currX = mCurrPos.getX();
	int currY = mCurrPos.getY();

	int minX = mTopLeft.getX() + 1;
	int minY = mTopLeft.getY() + 1;

	int maxX = mBottomRight.getX() - mWidth;
	int maxY = mBottomRight.getY() - mHeight;

	// Not allow the people move to outside
	if (currX <= minX)
		currX = minX;
	if (currX >= maxX)
		currX = maxX;

	if (currY >= maxY)
		currY = maxY;
	if (currY <= minY)
		currY = minY;

	mCurrPos.setXY(currX, currY);
}

void CPEOPLE::Up(int delta) {
	mCurrPos.moveY(-delta);
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
}

void CPEOPLE::Move(DIRECTION direction, int delta) {
	if (direction == DIRECTION::STAND_STILL) {
		return;
	}

	switch (direction) {
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
	default:
		return;
	}
	Clip();
}

bool CPEOPLE::isImpact(const vector<CVEHICLE>& allVehicles) {
	return false;
}

bool CPEOPLE::isImpact(const vector<CANIMAL>&) {
	return false;
}

bool  CPEOPLE::isFinish() const {
	if (mCurrPos.getY() <= mTopLeft.getY() + 1)
		return true;

	return false;
}

bool  CPEOPLE::isDead() const {
	return !mState;
}

void CPEOPLE::drawPeople(const Console& console) const {
	int x = mCurrPos.getX();
	int y = mCurrPos.getY();

	switch (mMovingDirection)
	{
	case DIRECTION::LEFT:
		console.DrawObject(x, y, mPeopleLeftForm,PEOPLE_COLOUR);
		break;
	case DIRECTION::RIGHT:
		console.DrawObject(x, y, mPeopleRightForm, PEOPLE_COLOUR);
		break;
	default:
		break;
	}
}