#include "CTRUCK.h"

CTRUCK::CTRUCK() {
	this->mVehicleLeftForm = "   __   __________ \n"
							 " _//]| |          |\n"
							 "|____|-|__________|\n"
							 "   O     O      O    ";

	this->mVehicleRightForm = " __________   __   \n"
							  "|          | |[\\\\_ \n"
							  "|__________|-|____| \n"
							  "  O     O      O   ";

	this->mHeight = GetHeightAsciiArt(this->mVehicleLeftForm);
	this->mWidth = GetWidthAsciiArt(this->mVehicleLeftForm);
	this->mMovingDirection = RandomInt(2,0) ? DIRECTION::LEFT : DIRECTION::RIGHT;
}

void CTRUCK::drawVehicle() {
	int startChar = 0;
	int nChar = 0;
	stringstream sstream;
	string tempStr = "";
	int line = 0;
	int x = this->mCurrPos.getX();
	int y = this->mCurrPos.getY();

	/*if (this->mX <= this->mSrcPoint.getX()) {
		startChar = 0 - this->mX;
		nChar = this->mWidth - startChar;
	}
	else {
		if (this->mX >= this->mDesPoint.getX()) {
			nChar = this->mDesPoint.getX() - this->mX;
		}
		else {
			nChar = this->mWidth;
		}
	}*/

	if (this->mMovingDirection == DIRECTION::LEFT) {
		sstream << this->mVehicleLeftForm;
	}
	else {
		
		sstream << this->mVehicleRightForm;
	}

	while (getline(sstream, tempStr, '\n')) {
		GotoXY(x + startChar + 1,y + line++);
		cout << tempStr.substr(startChar, nChar);
 	}
}