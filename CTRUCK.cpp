#include "CTRUCK.h"

CTRUCK::CTRUCK() {
	mCurrPos = CPOINT2D(0, 0);

	mVehicleLeftForm = "   __   ________ \n"
					   " _//]| |        |\n"
					   "|____|-|________|\n"
					   "   O     O    O    ";

	mVehicleRightForm = " ________   __   \n"
						"|        | |[\\\\_ \n"
						"|________|-|____|\n"
				   	    "  O   O      O   ";

	mHeight = mVehicleRightForm.Height();
	mWidth = mVehicleRightForm.Width();

	mSpeed = 0;

	mCurrVehicleForm = &mVehicleLeftForm;
	mVehicleColour = TRUCK_COLOUR;
}

CTRUCK::CTRUCK(const CTRUCK& other) {
	// Current position
	mCurrPos = other.mCurrPos;

	// Width and height of vehicle
	mHeight = other.mHeight;
	mWidth = other.mWidth;

	// Limit left and right X
	mLeft = other.mLeft;
	mRight = other.mRight;

	// Speed of vehicle
	mSpeed = other.mSpeed;

	// Vehicle form
	mVehicleLeftForm = other.mVehicleLeftForm;
	mVehicleRightForm = other.mVehicleRightForm;

	// Assign pointer
	if (other.mCurrVehicleForm == &other.mVehicleLeftForm) {
		mCurrVehicleForm = &mVehicleLeftForm;
	}
	else {
		mCurrVehicleForm = &mVehicleRightForm;
	}

	// Color for vehicle
	mVehicleColour = other.mVehicleColour;
}



