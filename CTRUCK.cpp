#include "CTRUCK.h"

CTRUCK::CTRUCK() {
	mVehicleLeftForm = "   __   ________ \n"
					   " _//]| |        |\n"
					   "|____|-|________|\n"
					   "   O     O    O    ";

	mVehicleRightForm = " ________   __   \n"
						"|        | |[\\\\_ \n"
						"|________|-|____| \n"
				   	    "  O   O      O   ";

	mHeight = mVehicleLeftForm.Height();
	mWidth = mVehicleLeftForm.Width();

	mVehicleColour = TRUCK_COLOUR;
}

CTRUCK::CTRUCK(int x, int y, int left, int right) : CTRUCK() {
	setXY(x, y);
	setLimit(left, right);
}
