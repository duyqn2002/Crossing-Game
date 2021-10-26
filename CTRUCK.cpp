#include "CTRUCK.h"

CTRUCK::CTRUCK() {
	mVehicleLeftForm = "   __   __________ \n"
					   " _//]| |          |\n"
					   "|____|-|__________|\n"
					   "   O     O      O    ";

	mVehicleRightForm = " __________   __   \n"
						"|          | |[\\\\_ \n"
						"|__________|-|____| \n"
				   	    "  O     O      O   ";

	mHeight = GetHeightAsciiArt(mVehicleLeftForm);
	mWidth = GetWidthAsciiArt(mVehicleLeftForm);
	//mMovingDirection = RandomInt(2,0) ? DIRECTION::LEFT : DIRECTION::RIGHT;
	mMovingDirection = DIRECTION::RIGHT;
}
