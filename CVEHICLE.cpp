#include "CVEHICLE.h"

CVEHICLE::CVEHICLE() {
	this->mSrcX = 0;
	this->mDesX = 0;

	this->mHeight = 0;
	this->mWidth = 0;

	this->mMovingDirection = DIRECTION::LEFT;
	this->mVehicleLeftForm = "";
	this->mVehicleRightForm = "";
}

CVEHICLE::~CVEHICLE() {}

void CVEHICLE::setXY(int x, int y) {
	this->mCurrPos.setXY(x, y);
}

void CVEHICLE::Move(int deltaX, int deltaY) {
	this->mCurrPos.moveXY(deltaX,deltaY);
}

void CVEHICLE::eraseVehicleHead() {
	int line = 0;
	int x = this->mCurrPos.getX();
	int y = this->mCurrPos.getY();
	while (line < this->mHeight) {
		GotoXY(x, y + line++);
		cout << " ";
	}
}

void CVEHICLE::eraseVehicleTail() {
	int line = 0;
	int x = this->mCurrPos.getX() + this->mWidth;
	int y = this->mCurrPos.getY();
	while (line < this->mHeight) {
		GotoXY(x ,y + line++);
		cout << " ";
	}
}

void CVEHICLE::erase(){
	/*if (this->mMovingDirection == Direction::LEFT) {
		if (this->mX <= this->mSrcX) {
			this->eraseVehicleHead();
		}
		else {
			if (this->mX >= this->mDesX) {
				this->eraseVehicleTail();
			}
		}
		this->eraseVehicleTail();
	}
	else {
		if (this->mX <= this->mDesPoint.getX()) {
			this->eraseVehicleHead();
		}
		else {
			if (this->mX >= this->mSrcPoint.getX()) {
				this->eraseVehicleTail();
			}
		}
		this->eraseVehicleHead();
	}*/
}

void CVEHICLE::drawVehicle() {}

void CVEHICLE::updatePos(int deltaX) {
	switch (this->mMovingDirection)
	{
		case DIRECTION::LEFT:
			this->Move(-deltaX, 0);
			break;
		case DIRECTION::RIGHT:
			
			this->Move(deltaX, 0);
			break;
	}
}

bool CVEHICLE::isHitLimit() const {
	bool isOutSide = false;
	int maxX, minX;
	int x = this->mCurrPos.getX();
	minX = this->mSrcX - this->mWidth;
	maxX = this->mDesX;
	

	switch (this->mMovingDirection)
	{
	
	case DIRECTION::LEFT:
		if (x == minX)
			isOutSide = true;
		break;

	case DIRECTION::RIGHT:
		if (x == maxX)
			isOutSide = true;
		break;
	}

	return isOutSide;
}

