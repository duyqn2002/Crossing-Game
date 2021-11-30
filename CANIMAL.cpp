#include "CANIMAL.h"

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

void CANIMAL::storeData(ofstream& ofs)
{
	ofs.write(reinterpret_cast<char*> (&mCurrPos), sizeof(CPOINT2D));

	bool state = false;
	if (mCurrAnimalForm == &mAnimalLeftForm)
		state = true;
	ofs.write(reinterpret_cast<char*> (&state), sizeof(bool));
}

void CANIMAL::loadData(ifstream& ifs)
{
	ifs.read(reinterpret_cast<char*> (&mCurrPos), sizeof(CPOINT2D));

	bool state = false;
	ifs.read(reinterpret_cast<char*> (&state), sizeof(bool));
	mCurrAnimalForm = (state) ? &mAnimalLeftForm : &mAnimalRightForm;
}

void CANIMAL::drawToConsole(Console& console,int leftLimit, int rightLimit) {
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