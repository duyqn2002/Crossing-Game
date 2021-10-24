#include "CPOINT2D.h"

CPOINT2D::CPOINT2D() {
	this->mX = 0;
	this->mY = 0;
}

void CPOINT2D::setX(int x) {
	this->mX = x;
}

void CPOINT2D::setY(int y) {
	this->mY = y;
}

void CPOINT2D::setXY(int x, int y) {
	this->setX(x);
	this->setY(y);
}

void CPOINT2D::moveX(int deltaX) {
	this->mX += deltaX;
}
void CPOINT2D::moveY(int deltaY) {
	this->mY += deltaY;
}
void CPOINT2D::moveXY(int deltaX, int deltaY) {
	this->moveX(deltaX);
	this->moveY(deltaY);
}

int CPOINT2D::getX() const {
	return this->mX;
}
int CPOINT2D::getY() const {
	return this->mY;
}
